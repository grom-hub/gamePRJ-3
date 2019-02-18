#include "units.h"

#include <ncurses.h>


Units::Units(char p1, int p2, int p3)
{
	pSkin = p1;
	pX = p2;
	pY = p3;
}

Units::~Units()
{

}

void Units::moveX(int p1)
{
	pX += p1;
}

void Units::moveY(int p1)
{
	pY += p1;
}

int Units::getX()
{
	return pX;
}

int Units::getY()
{
	return pY;
}

void Units::print()
{
	mvaddch(pX, pY, pSkin);
}
