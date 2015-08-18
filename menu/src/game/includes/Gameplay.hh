//
// Gameplay.hh for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 14:01:59 2014 brunne-r
// Last update Sat Jun  7 17:27:54 2014 BLANCHARD
//

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

# include <vector>
# include <iostream>
# include <pthread.h>
# include <unistd.h>
# include <sstream>
# include "Maps.hh"
# include "Player.hh"
# include "Bomb.hh"
# include "Command.hh"

class	Gameplay
{
private:
  Maps				*_map;
  std::vector<Player*>     _ps;
  std::vector<Bomb*>       _bombs;

public:
  Gameplay(std::string path_map);
  ~Gameplay(void);

  void        setMap(Maps *ptr_map);
  const Maps	*getMap(void) const;
  void		resetPlayers(void);
  bool		addPlayer(int id, const std::string &name);
  void    dump() const;
  void		run(void);
  bool		do_action(int id, Command::Action action);
  void    manageBombs();
  std::string    getCharMap(int range, int idp);
};

static void  *runBomb(void *arg);

#endif /* !GAMEPLAY_H */
