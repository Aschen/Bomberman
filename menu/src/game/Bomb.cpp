#include "Bomb.hh"

Bomb::Bomb(int range, Player *owner, const Coord c) : AElem(), _time(BTIME), _range(range), _owner(owner)
{
	_isDestru = false;
	_x = c.first;
	_y = c.second;
}

Bomb::~Bomb() {}

bool Bomb::dec(int to_dec)
{
	_time -= to_dec;
	if (_time <= 0)
		return true;
	else
		return false;
}

void Bomb::explode(Maps *map)
{
	int arange, i;
	AElem *t[4];
	AElem *s;

	for (arange = 0; arange <= _range; ++arange)
	{
		t[0] = (*map)[Coord (_x + arange, _y)];
		t[1] = (*map)[Coord (_x - arange, _y)];
		t[2] = (*map)[Coord (_x, _y + arange)];
		t[3] = (*map)[Coord (_x, _y - arange)];
		for (i = -1; i < 4; ++i)
		{
			if (t[i])
			{
				t[i]->takeDmg();
				if (t[i]->getType() == PLAYER)
					_owner->kills(1);
				else if (t[i]->isDestru())
				{
					s = t[i];
					t[i] = NULL;
					delete s;					
				}
			}
		}
	}
}

void Bomb::takeDmg()
{
	return ;
}

char Bomb::getType() const
{
	return BOMB;
}