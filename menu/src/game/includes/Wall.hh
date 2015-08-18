#ifndef WALLHH
#define WALLHH

#include "AElem.hh"

class Wall : public AElem
{
public:
	explicit Wall(int x, int y);
	~Wall();
	void takeDmg();
	char getType() const;
};

#endif