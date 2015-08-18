#ifndef BOMB_HH
#define BOMB_HH

#include <ctime>
#include "Player.hh"
#include "Bomb.hh"
#include "Maps.hh"
#include "AElem.hh"

#define BTIME 2

class Bomb : public AElem
{
private:
	int 	_time;
	int 	_range;
	Player*	_owner;
public:
	explicit Bomb(int range, Player* owner, const Coord c);
	~Bomb();
	bool dec(int to_dec);
	void explode(Maps *map);
	void takeDmg();
	char getType() const;
};

#endif /* BOMB_HH */