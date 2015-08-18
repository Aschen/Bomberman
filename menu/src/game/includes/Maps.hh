//
// maps.hh for maps in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Tue May  6 11:05:01 2014 Thibaut Sabot
// Last update Fri May  9 10:15:54 2014 brunne-r
//

#ifndef	MAPS_HH
# define MAPS_HH

#include <map>
#include "AElem.hh"
#include "Command.hh"

typedef std::pair<int, int> Coord;
typedef std::map<Coord, AElem*> Map;

class	Maps
{
  /* Structure nécessaire pour la sérialisation (peut etre remplacer par une classe) */
  typedef struct s_read
  {
    char content[4096];
  }		t_read;

private:
  Map	_map;
  int _width;
  int _height;

private:
  bool	checkAccess(const std::string &path);
  void	writeToFile(const std::string &path, std::string content);
  std::string	stringToInt(int number);
  std::string	getPath(std::string path);
  void makeSaveFiles(const std::string &path);
  void	readContent(const std::string &path);

public:
  Maps();
  ~Maps();
  void	save();
  void	load(const std::string &path);
  void	create(int size_x, int size_y, int density);
  bool  isFree(Command::Action direction, Coord& to);
  int   width() const;
  int   height() const;
  void  assign(AElem* elem, Coord offset);
  AElem	*operator[](Coord offset);
};

#endif
