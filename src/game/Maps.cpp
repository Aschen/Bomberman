//
// maps.cpp for maps in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Tue May  6 11:04:02 2014 Thibaut Sabot
// Last update Wed Jun 25 11:36:16 2014 Thibaut Sabot
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
  std::cout << "~MAP" << std::endl;
  for_each(_map.begin(), _map.end(), &delete_it);
  std::cout << "MAP~" << std::endl;
}

bool	Maps::checkAccess(const std::string &path) const
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

void	Maps::writeToFile(std::ofstream &ofs, const std::string &path, AElem *e) const
{
  Player *p(NULL);
  t_read  tow;
  Coord c;
  std::string n;

  if (e->getType() == PLAYER)
    p = dynamic_cast<Player*>(e);
  c = e->getCoord();
  tow.type = e->getType();
  tow.x = c.first;
  tow.y = c.second;
  memset(tow.name, 0, 500);
  if (p)
  {
    tow.kills = p->kills();
    tow.deaths = p->deaths();
    tow.id = p->id();
    n = p->name();
    strncpy(tow.name, n.c_str(), (n.size() > 499) ? 499 : n.size());
  }    
  ofs.write((char *)&tow, sizeof(tow));
}

std::string	Maps::stringToInt(int number) const
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}

std::string	Maps::getPath(std::string path) const
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

void	Maps::makeSaveFiles(const std::string &path) const
{
  Map::const_iterator it, end;
  int len;
  it = _map.begin();
  end = _map.end();
  std::cout << "Save in " << path << std::endl;
  std::ofstream ofs(path.c_str(), std::ios::binary);
  len = _map.size();
  std::cout << "Save " << len << " objects" << std::endl;
  ofs.write((char*)(&len), sizeof(len));
  ofs.write((char*)(&_width), sizeof(len));
  ofs.write((char*)(&_height), sizeof(len));
  while (it != end)
  {
    if ((*it).second)
      writeToFile(ofs, path, (*it).second);
    ++it;
  }  
}

void	Maps::save(const std::string &file) const
{
  std::string	path;

  path = ".";
  if (checkAccess(path) == true)
    {
      path = getPath(path);
      makeSaveFiles(path + file);
    }
  else
    std::cerr << "Path doesn't exist or is a file" << std::endl;
}

void	Maps::readContent(const std::string &path)
{
  t_read tow;
  int len;
  AElem *top;
  Player *p;
  GBox *b;
  Wall *w;

  std::ifstream ifs(path.c_str(), std::ios::binary);
  ifs.read((char*)(&len), sizeof(len));
  ifs.read((char*)(&_width), sizeof(len));
  ifs.read((char*)(&_height), sizeof(len));
  std::cout << "Load " << len << " objects" << std::endl;
  for (int i = 0; i < len; i++)
  {
    ifs.read((char *)&tow, sizeof(tow));
    switch (tow.type)
    {
    case PLAYER:
      p = new Player(tow.id, std::string(tow.name));
      p->move(Coord(tow.x, tow.y));
      p->deaths(tow.deaths);
      p->kills(tow.kills);
      top = p;
      break;
    case BOX:
      b = new GBox(tow.x, tow.y);
      top = b;
      break;
    case WALL:
      w = new Wall(tow.x, tow.y);
      top = w;
      break;
    }
    _map.insert(std::pair<Coord, AElem*>(top->getCoord(), top));
  }
}

void	Maps::load(const std::string &path)
{
  if (checkAccess(path) == true)
    {
      for_each(_map.begin(), _map.end(), &delete_it);
      _map.clear();
      readContent(path + "map.save");
    }
  else
    std::cerr << "Path doesn't exist or is a file" << std::endl;
}


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
        if (x == 0 || y == 0 || x == size_x || y == size_y)
          _map[std::pair<int, int>(x, y)] = new Wall(x, y);
        else
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
  {
    if (to.first < 0 || to.second < 0)
      return false;
    else if (to.first >= _width || to.second >= _height)
      return false;
    else
      return true;
  }
  else
    return false;
}

bool  Maps::isFree(direction dir, Coord& to)
{
  switch (dir)
    {
    case UP :
      --to.second;
      break;
    case DOWN :
      ++to.second;
      break;
    case LEFT :
      --to.first;
      break;
    case RIGHT :
      ++to.first;
      break;
    default:
       break;
    }
  if ((*this)[to] == NULL)
  {
    if (to.first < 0 || to.second < 0)
      return false;
    else if (to.first >= _width || to.second >= _height)
      return false;
    else
      return true;
  }
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

void  Maps::assign(AElem* elem, const Coord offset)
{  
    if (elem == NULL)
        _map.erase(offset);
    else
       _map[offset] = elem;
}
