#include "GBox.hh"

GBox::GBox(int x, int y) : AElem()
{
	_x = x;
	_y = y;
	_isDestru = true;
}

GBox::~GBox()
{
}

void GBox::takeDmg()
{
	return ;
}

char GBox::getType() const
{
	return BOX;
}