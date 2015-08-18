#include "Bomb.hh"
#include "GFlames.hh"

Bomb::Bomb(int range, Player *owner, const Coord c) : AElem(), _time(3000000), _range(BTIME), _owner(NULL)
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

void Bomb::explode(Maps *map, std::vector<GFlames*>& v)
{
	int arange, i;
	AElem *t[4];
	Coord cs[4];
	Coord c;
	Player *pl;

	for (arange = 1; arange <= _range; arange++)
	{
		cs[0] = Coord (_x + arange, _y);
		cs[1] = Coord (_x - arange, _y);
		cs[2] = Coord (_x, _y + arange);
		cs[3] = Coord (_x, _y - arange);
		t[0] = (*map)[cs[0]];
		t[1] = (*map)[cs[1]];
		t[2] = (*map)[cs[2]];
		t[3] = (*map)[cs[3]];
		for (i = 0; i < 4; i++)
		{
			if (t[i])
			{				
				c = t[i]->getCoord();				
				t[i]->takeDmg();
				if (t[i]->isDestru())
				{
					if (t[i]->getType() != PLAYER)
					{
						if (t[i]->getType() != WALL)
						{
							v.push_back(new GFlames(c.first, c.second));
							map->assign(v.back(), c);
						}											
						delete t[i];
					}
					else
					{
						pl = dynamic_cast<Player*>(t[i]);
						pl->move(pl->getSpawn());
						map->assign(NULL, c);
						map->assign(pl, pl->getSpawn());
					}
				}
			}
			else
			{
				v.push_back(new GFlames(cs[i].first, cs[i].second));
				map->assign(v.back(), cs[i]);
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