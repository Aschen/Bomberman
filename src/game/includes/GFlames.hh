#ifndef GFAHH
#define GFAHH

#include "AElem.hh"

class GFlames : public AElem
{
private:
	int _time;
public:
	explicit GFlames(int x, int y);
	~GFlames();
	void takeDmg();
	char getType() const;
	bool dec(int to_dec);
};

#endif