//
// maps.hh for maps in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Tue May  6 11:05:01 2014 Thibaut Sabot
// Last update Wed Jun 25 11:36:13 2014 Thibaut Sabot
//

#ifndef	MAPS_HH
# define MAPS_HH

#include <map>
#include "AElem.hh"
#include "Command.hh"
#include "Player.hh"

typedef std::pair<int, int> Coord;
typedef std::map<Coord, AElem*> Map;

class	Maps
{
private:
  /* Structure nécessaire pour la sérialisation (peut etre remplacer par une classe) */
  typedef struct s_read
  {
    char  type;
    int   x;
    int   y;
    int   kills;
    int   deaths;
    char  name[500];
    int   id;
  }		           t_read;

private:
  Map	_map;
  int _width;
  int _height;

private:
  bool	checkAccess(const std::string &path) const;
  void	writeToFile(std::ofstream &ofs, const std::string &path, AElem *e) const;
  std::string	stringToInt(int number) const;
  std::string	getPath(std::string path) const;
  void makeSaveFiles(const std::string &path) const;
  void	readContent(const std::string &path);

public:
  Maps();
  ~Maps();
  void	save(const std::string &file) const;
  void	load(const std::string &path);
  void	create(int size_x, int size_y, int density);
  bool  isFree(Command::Action direction, Coord& to);
  bool  isFree(direction dir, Coord& to);
  int   width() const;
  int   height() const;
  void  assign(AElem* elem, const Coord offset);
  AElem	*operator[](Coord offset); 
};

#endif
