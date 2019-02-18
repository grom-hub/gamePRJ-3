#include <ncurses.h>
#include <unistd.h> // usleep()
#include <cstdlib> // rand(), srand(), exit()
#include <ctime> // time()
//#include <string>
//#include <vector>



int main()
{
	int key;
	int slctP = 0;

	char pSkin[3] = {'A', 'B', 'C'};
	int pX[3] = {2, 2, 2};
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
    	wX[i] = 4 + rand() % 15;
    	wY[i] = 1 + rand() % 40;
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
			pX[slctP]++;
			moveId = 1;
		}
		if (key == KEY_UP)
		{
			pX[slctP]--;
			moveId = 2;
		}
		if (key == KEY_RIGHT)
		{
			pY[slctP]++;
			moveId = 3;
		}
		if (key == KEY_LEFT)
		{
			pY[slctP]--;
			moveId = 4;
		}
		if (key == ' ')
		{
			slctP++;
			if (slctP > 2)
				slctP = 0;
		}
///////////////////

/////////////////// Если было движение, проверить не столкновение.
		if(moveId != 0)
		{
			cTest = 0;

			if(pX[slctP] > LINES-2 || pX[slctP] < 1 || pY[slctP] > COLS-3 || pY[slctP] < 2)
			{
				cTest = 1;
			}
			
			for (int i = 0; i < 10; i++)
			{
				if(pX[slctP] == wX[i] && pY[slctP] == wY[i])
				{
					cTest = 1;
					break;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if(slctP != i && pX[slctP] == pX[i] && pY[slctP] == pY[i])
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
					pX[slctP]--;
					break;
				case 2:
					pX[slctP]++;
					break;
				case 3:
					pY[slctP]--;
					break;
				case 4:
					pY[slctP]++;
					break;
			}
		}
///////////////////
	}



	endwin();
	return 0;
}