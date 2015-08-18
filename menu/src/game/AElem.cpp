#include "AElem.hh"

AElem::AElem() : _x(0), _y(0), _isDestru(true)
{}

AElem::~AElem()
{}

Coord	AElem::getCoord() const
{
	Coord c(_x, _y);
	return c;
}

bool AElem::isDestru() const
{
	return _isDestru;
}
