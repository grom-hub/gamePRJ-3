#include <ncurses.h>
#include <unistd.h> // usleep()
#include <cstdlib> // rand(), srand(), exit()
#include <ctime> // time()
//#include <string>
//#include <vector>

#include "units.h"
#include "walls.h"


int main()
{
	int key;
	int slctU = 0;

	int moveId = 0;
	int cTest = 0;



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

	Units unit[3] =
	{
		Units('A', 2, 2),
		Units('B', 2, 4),
		Units('C', 2, 6)
	};

	Walls wall[20];


	while(key != 'q')
	{
		usleep(10000); // Частота обновления.

/////////////////// Вывод на экран.
		clear();
		box(stdscr, 0,0);
		for(int i = 0; i < 20; i++)
		{
			wall[i].print();					
		}
		for (int i = 0; i < 3; i++)
		{
			unit[i].print();
		}
		refresh();
/////////////////
		
/////////////////// Проверка нажатых клавиш.
		key = getch(); 
		// for (int slctU = 0; slctU < 3; slctU++) // Одновременное движение.
		// {
		moveId = 0;

		if (key == KEY_DOWN)
		{
			unit[slctU].moveX(1);
			moveId = 1;
		}
		if (key == KEY_UP)
		{
			unit[slctU].moveX(-1);
			moveId = 2;
		}
		if (key == KEY_RIGHT)
		{
			unit[slctU].moveY(1);
			moveId = 3;
		}
		if (key == KEY_LEFT)
		{
			unit[slctU].moveY(-1);
			moveId = 4;
		}
		if (key == ' ')
		{
			slctU++;
			if (slctU > 2)
				slctU = 0;
		}
///////////////////

/////////////////// Если было движение, проверить не столкновение.
		if(moveId != 0)
		{
			cTest = 0;

			if(	unit[slctU].getX() > LINES-2 
				|| unit[slctU].getX() < 1 
				|| unit[slctU].getY() > COLS-2 
				|| unit[slctU].getY() < 1 )
			{
				cTest = 1;
			}
			
			for (int i = 0; i < 20; i++)
			{
				if( unit[slctU].getX() == wall[i].getX() 
					&& unit[slctU].getY() == wall[i].getY() )
				{
					cTest = 1;
					break;
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if(	slctU != i && unit[slctU].getX() == unit[i].getX() 
					&& unit[slctU].getY() == unit[i].getY() )
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
					unit[slctU].moveX(-1);
					break;
				case 2:
					unit[slctU].moveX(1);
					break;
				case 3:
					unit[slctU].moveY(-1);
					break;
				case 4:
					unit[slctU].moveY(1);
					break;
			}
		}
	// }
///////////////////
	}



	endwin();
	return 0;
}