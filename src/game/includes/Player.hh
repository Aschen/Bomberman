//
// Player.hh for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 12:12:13 2014 brunne-r
// Last update Wed Jun 25 11:35:52 2014 Thibaut Sabot
//

#ifndef PLAYER_H
# define PLAYER_H

# include <map>
# include "Command.hh"
# include "AElem.hh"
# include "ABonus.hh"

class	Player : public AElem
{
private:
  std::string _name;
  int         _id;
  int         _kills;
  int         _deaths;
  ABonus::Bonus	_bonus;
  direction   _d;
  std::map<Command::Action, direction> _links;
  Coord _spawn;

public:
  Player(int id, const std::string &name);
  ~Player();
  void  takeDmg();
  char  getType() const;
  bool	move(const Coord &nc);
  void	die() const;
  int   id() const;
  std::string name() const;
  int kills() const;
  void kills(int score);
  int deaths() const;
  void setDir(const Command::Action act);
  void deaths(int score);
  direction getDir() const;
  void saveSpawn();
  Coord getSpawn() const;
};

#endif /* !PLAYER_H */
