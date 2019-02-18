#include <ncurses.h>
#include <unistd.h> // usleep()
#include <cstdlib> // rand(), srand(), exit()
#include <ctime> // time()
//#include <string>
//#include <vector>



int main()
{
	int key;
	int slct = 0;

	char pSkin[3] = {'A', 'B', 'C'};
	int pX[3] = {2, 4, 6};
	int pY[3] = {2, 4, 6};

	int moveId = 0;
	int cTest = 0;

	char wSkin = '#';
	int wX[10];
	int wY[10];


	if (!initscr())
    {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    clear();
    refresh();

	srand(time(0));



    for(int i = 0; i < 10; i++) // Расстановка стен
    {
    	wX[i] = 1 + rand() % 20;
    	wY[i] = 1 + rand() % 20;
    }


	while(key != 'q')
	{
		usleep(10000); // Частота обновления.

/////////////////// Вывод на экран.
		clear();
		box(stdscr, 0,0);
		for(int i = 0; i < 10; i++)
		{
			mvaddch(wX[i], wY[i], wSkin);					
		}
		for (int i = 0; i < 3; i++)
		{
		mvaddch(pX[i], pY[i], pSkin[i]);
		}
		refresh();
/////////////////

/////////////////// Проверка нажатых клавиш.
		key = getch(); 
		moveId = 0;

		if (key == KEY_DOWN)
		{
			pX[slct]++;
			moveId = 1;
		}
		if (key == KEY_UP)
		{
			pX[slct]--;
			moveId = 2;
		}
		if (key == KEY_RIGHT)
		{
			pY[slct]++;
			moveId = 3;
		}
		if (key == KEY_LEFT)
		{
			pY[slct]--;
			moveId = 4;
		}
		if (key == ' ')
		{
			slct++;
			if (slct > 2)
				slct = 0;
		}
///////////////////

/////////////////// Если было движение, проверить не столкновение.
		if(moveId != 0)
		{
			cTest = 0;

			if(pX[slct] > LINES-2 || pX[slct] < 1 || pY[slct] > COLS-3 || pY[slct] < 2)
			{
				cTest = 1;
			}
			
			for (int i = 0; i < 10; i++)
			{
				if(pX[slct] == wX[i] && pY[slct] == wY[i])
				{
					cTest = 1;
					break;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if(slct != i && pX[slct] == pX[i] && pY[slct] == pY[i])
				{
					cTest = 1;
					break;
				}
			}
		}
/////////////////// Если обнаружено столкновение, отменить движение.
		if(cTest == 1)
		{
			switch (moveId)
			{
				case 1:
					pX[slct]--;
					break;
				case 2:
					pX[slct]++;
					break;
				case 3:
					pY[slct]--;
					break;
				case 4:
					pY[slct]++;
					break;
			}
		}
///////////////////
	}



	endwin();
	return 0;
}