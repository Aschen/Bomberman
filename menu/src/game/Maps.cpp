//
// maps.cpp for maps in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Tue May  6 11:04:02 2014 Thibaut Sabot
// Last update Wed Jun 25 23:14:44 2014 Thibaut Sabot
//

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Maps.hh"
#include "GBox.hh"
#include "Wall.hh"

void delete_it(std::pair<Coord, AElem*> elem)
{
  if (elem.second && (elem.second)->getType() != PLAYER)
  {    
    delete elem.second;    
  }
}

Maps::Maps()
{
  srand(time(NULL));
}

Maps::~Maps()
{
  for_each(_map.begin(), _map.end(), &delete_it);
}

bool	Maps::checkAccess(const std::string &path)
{
  if (access(path.c_str(), 0) == 0)
    {
      struct stat status;

      stat(path.c_str(), &status);
      if (status.st_mode & S_IFDIR)
	     return (true);
      else
	     return (false);
    }
  return (false);
}

void	Maps::writeToFile(const std::string &path, std::string content)
{
  t_read _read;

  strcpy(_read.content, content.c_str());
  std::ofstream ofs(path.c_str(), std::ios::binary);
  ofs.write((char *)&_read, sizeof(_read));
}

std::string	Maps::stringToInt(int number)
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}

std::string	Maps::getPath(std::string path)
{
  int		i;
  const char	*filename;

  i = 1;
  if (path.length() - 1 != '/')
    path = path + "/";
  while (checkAccess(path + "game_" + stringToInt(i)) == true)
    i++;
  filename = (path + "game_" + stringToInt(i)).c_str();
  mkdir(filename, 0775);
  path = path + "game_" + stringToInt(i) + "/";
  return (path);
}

void	Maps::makeSaveFiles(const std::string &path)
{
  std::string	content;

  content = "Map Serial";
  writeToFile(path + "map.ros", content);
  content = "Player1 Serial";
  writeToFile(path + "player1.ros", content);
  content = "Player2 Serial";
  writeToFile(path + "player2.ros", content);
}

void	Maps::save()
{
  std::string	path;

  std::cout << "Enter saving directory: ";
  std::cin >> path;
  if (checkAccess(path) == true)
    {
      path = getPath(path);
      makeSaveFiles(path);
    }
  else
    std::cerr << "Path doesn't exist or is a file" << std::endl;
}

void	Maps::readContent(const std::string &path)
{
  t_read _read;

  std::ifstream ifs(path.c_str(), std::ios::binary);
  ifs.read((char *)&_read, sizeof(_read));
  std::cout << path << " : " << _read.content << std::endl;
}

void	Maps::load(const std::string &path)
{
  if (checkAccess(path) == true)
    {
      readContent(path + "map.ros");
      readContent(path + "player1.ros");
      readContent(path + "player2.ros");
    }
  else
    std::cerr << "Path doesn't exist or is a file" << std::endl;
}

/*
    Gen aléatoire :
  - Ne pas se tuer au spawn si besoin de détruire object
  - Essayer de faire des couloirs
*/
void	Maps::create(int size_x, int size_y, int density)
{
    int x, y;
    float r(0.0);

    _height = size_y;
    _width = size_x;
    for (x = 0; x <= size_x; ++x)
    {
      for (y = 0; y <= size_y; ++y)
      {
        r = rand() % 101;
        if (r < density)
        {
          r = rand() % 2;
          if (r)
            _map[std::pair<int, int>(x, y)] = new GBox(x, y);       
          else
            _map[std::pair<int, int>(x, y)] = new Wall(x, y);
        }
      }
    }
}

/*
  Permet d'accèder à un éléments comme ce serait le cas pour un tableau
  à double entrées.
*/
AElem	*Maps::operator[](Coord offset)
{
  AElem* toret;

  if (!(toret = _map[offset]))
  {
    _map.erase(offset);
    return NULL;
  }
  else
    return toret;
}

bool Maps::isFree(Command::Action direction, Coord& to)
{
  switch (direction)
    {
    case Command::UP :
      --to.second;
      break;
    case Command::DOWN :
      ++to.second;
      break;
    case Command::LEFT :
      --to.first;
      break;
    case Command::RIGHT :
      ++to.first;
      break;
    default:
       break;
    }
  if ((*this)[to] == NULL)
    return true;
  else
    return false;
}

int   Maps::width() const
{
  return _width;
}

int   Maps::height() const
{
  return _height;
}

void  Maps::assign(AElem* elem, Coord offset)
{
  if (_map[offset] != NULL)
    delete _map[offset];
  _map[offset] = elem;
}
