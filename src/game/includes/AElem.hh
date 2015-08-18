//
// AElem.hh for AEleme in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Wed May  7 11:40:56 2014 Thibaut Sabot
// Last update Wed May  7 15:52:25 2014 brunne-r
//

#ifndef	AELEM_HH
# define	AELEM_HH

#include	<utility>
#include	<iostream>
#include    "Graph.hh"

typedef std::pair<int, int> Coord;

class	AElem
{

protected:
  int		_x;
  int		_y;  
  bool	_isDestru;

public:
  AElem();
  virtual ~AElem();
  Coord	getCoord() const;
  void    setCoord(Coord c);
  bool    isDestru() const;
  virtual void		takeDmg() = 0;
  virtual char		getType() const = 0;
};

#endif
