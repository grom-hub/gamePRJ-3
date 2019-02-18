#include <ncurses.h>
#include <unistd.h> // usleep()
#include <cstdlib> // rand(), srand(), exit()
#include <ctime> // time()
//#include <string>
//#include <vector>



int main()
{
	int key;

	char pSkin = 'A';
	int pX = 5;
	int pY = 5;

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



    for(int i = 0; i < 10; i++)
    {
    	wX[i] = 1 + rand() % 20;
    	wY[i] = 1 + rand() % 20;
    }


	while(key != 'q')
	{
		usleep(10000);

		clear();
		box(stdscr, 0,0);
		for(int i = 0; i < 10; i++)
		{
			mvaddch(wX[i], wY[i], wSkin);					
		}
		mvaddch(pX, pY, pSkin);
		refresh();

		key = getch();
		moveId = 0;
		if (key == KEY_DOWN)
		{
			pX++;
			moveId = 1;
		}
		if (key == KEY_UP)
		{
			pX--;
			moveId = 2;
		}
		if (key == KEY_RIGHT)
		{
			pY++;
			moveId = 3;
		}
		if (key == KEY_LEFT)
		{
			pY--;
			moveId = 4;
		}


		if(moveId != 0) // Если было движение, проверить не столкновение.
		{
			cTest = 0;

			if(pX > LINES-2 || pX < 1 || pY > COLS-3 || pY < 2)
			{
				cTest = 1;
			}
			
			for (int i = 0; i < 10; i++)
			{
				if(pX == wX[i] && pY == wY[i])
				{
					cTest = 1;
					break;
				}
			}
		}

		if(cTest == 1) // Если обнаружено столкновение, отменить движение.
		{
			switch (moveId)
			{
				case 1:
					pX--;
					break;
				case 2:
					pX++;
					break;
				case 3:
					pY--;
					break;
				case 4:
					pY++;
					break;
			}
		}
	}



	endwin();
	return 0;
}