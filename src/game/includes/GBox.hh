#ifndef GBOXHH
#define GBOXHH

#include "AElem.hh"

class GBox : public AElem
{
public:
	explicit GBox(int x, int y);
	~GBox();
	void takeDmg();
	char getType() const;
};

#endif