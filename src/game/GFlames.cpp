#include "GFlames.hh"

GFlames::GFlames(int x, int y) : AElem(), _time(500000)
{
	_x = x;
	_y = y;
	_isDestru = true;
}

GFlames::~GFlames()
{
}

void GFlames::takeDmg()
{
	return ;
}

char GFlames::getType() const
{
	return FLAMES;
}

bool GFlames::dec(int to_dec)
{
	_time -= to_dec;
	if (_time <= 0)
		return true;
	else
		return false;
}