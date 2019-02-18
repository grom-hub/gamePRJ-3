#include <ncurses.h>
#include <unistd.h> // usleep()
#include <cstdlib> // rand(), srand(), exit()
//#include <ctime> // time()
//#include <string>
//#include <vector>



int main()
{
	int key;

	char pSkin = 'A';
	int pX = 5;
	int pY = 5;



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

	

	while(key != 'q')
	{
		usleep(10000);

		clear();
		box(stdscr, 0,0);		
		mvaddch(pX, pY, pSkin);
		refresh();

		key = getch();
		if (key == KEY_DOWN && pX < LINES-2)
			pX++;
		if (key == KEY_UP && pX > 1)
			pX--;
		if (key == KEY_RIGHT && pY < COLS-3)
			pY++;
		if (key == KEY_LEFT && pY > 2)
			pY--;

	}



	endwin();
	return 0;
}