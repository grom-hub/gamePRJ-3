#include "walls.h"

#include <ncurses.h>
#include <cstdlib> // rand(), srand(), exit()



Walls::Walls()
{
	wSkin = '#';
	wX = 1 + rand() % (LINES - 2);
    wY = 1 + rand() % (COLS - 2);
}

Walls::~Walls()
{

}

void Walls::print()
{
	mvaddch(wX, wY, wSkin);
}

int Walls::getX()
{
	return wX;
}

int Walls::getY()
{
	return wY;
}