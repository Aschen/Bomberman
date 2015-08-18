#include "Wall.hh"

Wall::Wall(int x, int y) : AElem()
{
	_x = x;
	_y = y;
	_isDestru = false;
}

Wall::~Wall()
{
}

void Wall::takeDmg()
{
	return ;
}

char Wall::getType() const
{
	return WALL;
}