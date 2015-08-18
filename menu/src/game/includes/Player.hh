//
// Player.hh for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 12:12:13 2014 brunne-r
// Last update Wed May  7 15:36:44 2014 brunne-r
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

public:
  Player(int id, const std::string &name);
  ~Player();
  void  takeDmg();
  char  getType() const;
  bool	move(const Coord &nc);
  void	die();
  int   id() const;
  std::string name() const;
  int kills() const;
  void kills(int score);
  int deaths() const;
  void setDir(const Command::Action act);
};

#endif /* !PLAYER_H */
