//
// Gameplay.hh for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 14:01:59 2014 brunne-r
// Last update Wed Jun 25 11:28:15 2014 Thibaut Sabot
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
# include "Time.hh"
# include "GFlames.hh"

class	Gameplay
{
private:
  Maps				*_map;
  std::vector<Player*>::iterator _itp;
  std::vector<Player*>     _ps;
  std::vector<Bomb*>       _bombs;
  std::vector<GFlames*>    _fl;

  void		 littleSort(int nb_player);
  void		 rightSort(int first, int last, int number, int nb);
  void		 leftSort(int first, int last, int number, int nb);

public:
  Gameplay(std::string path_map);
  ~Gameplay(void);

  void        setMap(Maps *ptr_map);
  const Maps	*getMap(void) const;
  void		resetPlayers(void);
  bool		addPlayer(int id, const std::string &name);
  void    dump() const;
  void		run(void);
  bool		do_action(int id, const Command::Action &action);
  void    manageBombs();
  std::string    getCharMap(int range, int idp) const;
  void		 placePlayer();
  void     save(const std::string &file);
  void     load(const std::string &path);
  std::string    getComposition() const;
};

static void  *runBomb(void *arg);

#endif /* !GAMEPLAY_H */
