//
// Gameplay.cpp for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 14:58:01 2014 brunne-r
// Last update Wed Jun 25 23:22:36 2014 Thibaut Sabot
//

#include "Gameplay.hh"

Gameplay::Gameplay(std::string path_map)
{
  _map = new Maps();
  //  _map->load(path_map);
  _map->create(100, 100, 30);
}

Gameplay::~Gameplay(void)
{
  this->resetPlayers();
}

void Gameplay::setMap(Maps *ptr_map)
{
  this->resetPlayers();
  _map = ptr_map;
}

void Gameplay::resetPlayers(void)
{
  std::vector<Player*>::iterator it, end, actu;


  it = _ps.begin();
  end = _ps.end();
  while (it < end)
  {
    actu = it;
    ++it;
    _map->assign(NULL, (*actu)->getCoord());
  }
  _ps.clear();
}

bool Gameplay::addPlayer(int id, const std::string &name)
{
  std::vector<Player*>::const_iterator it, end;

  it = _ps.begin();
  end = _ps.end();
  while (it < end)
  {
    if ((*it)->id() == id)
      return false;
    ++it;
  }
  _ps.push_back(new Player(id, name));
  return true;
}

const Maps *Gameplay::getMap(void) const
{
  return _map;
}

bool  Gameplay::do_action(int id, const Command::Action &action)
{
  std::vector<Player*>::const_iterator it, end;
  Coord nc, old;
  AElem *a;
  bool b(false);

  it = _ps.begin();
  end = _ps.end();
  while (it < end)
  {
    if ((*it)->id() == id)
    {
      nc = (*it)->getCoord();
      old = nc;
      if (action >= Command::UP && action <= Command::RIGHT)
      {
        (*it)->setDir(action);
	       if (_map->isFree(action, nc) || ((*_map)[nc])->getType() == NONE)
	         b = true;
	     if (b)
	     {
	       if ((*it)->move(nc))
	       {
            _map->assign(NULL, old);
            _map->assign(*it, nc);
	       }
	}
	return b;
      }
      else if (action == Command::DBOMB)
	    {
      	if (_map->isFree((*it)->getDir(), nc))
        {
          _bombs.push_back(new Bomb(2, *it, nc));
          _map->assign(_bombs.back(), nc);
        }
      }
      else
       std::cout << "Pause." << std::endl;
      return true;
    }
    ++it;
  }
  std::cout << "No action." << std::endl;
  return false;
}

void  Gameplay::run(void)
{
  AElem *a;

  this->placePlayer();
}

void Gameplay::dump() const
{
  std::vector<Player*>::const_iterator it, end;

  it = _ps.begin();
  end = _ps.end();
}

void Gameplay::manageBombs()
{
  std::vector<Bomb*>::iterator it, end;
  std::vector<GFlames*>::iterator fit, fend;
  static int lastTime = Time::getMicroTimestamp();
  int timedec(0);
  Coord c;

  timedec = Time::getMicroTimestamp() - lastTime;
    if (_bombs.size() > 0)
    {
      it = _bombs.begin();
      end = _bombs.end();
      while (it < end)
      {
      	if ((*it)->dec(timedec))
      	{
      	  (*it)->explode(_map, _fl);
          c = (*it)->getCoord();
          _map->assign(NULL, (*it)->getCoord());
          delete *it;
          _bombs.erase(it);
          _fl.push_back(new GFlames(c.first, c.second));
          _map->assign(_fl.back(), c);
      	  break;
      	}
      	else
      	  ++it;
      }
    }
    if (_fl.size() > 0)
    {
      fit = _fl.begin();
      fend = _fl.end();
      while (fit < fend)
      {
        if ((*fit)->dec(timedec))
        {          
          _map->assign(NULL, (*fit)->getCoord());          
          delete *fit;
          _fl.erase(fit);
          break;
        }
        else
          ++fit;
      }
    }
    usleep(200);
    lastTime = Time::getMicroTimestamp();
}

std::string Gameplay::getCharMap(int range, int idp) const
{
  std::string aff;
  std::vector<Player*>::const_iterator it, end;
  Coord nc, start, last, a_away, b_away;
  int remember;
  std::string dirs;
  AElem *ptr;
  Player *pl;

  it = _ps.begin();
  end = _ps.end();
  while (it < end)
  {
    if ((*it)->id() == idp)
    {
      nc = (*it)->getCoord();

      start.first = (nc.first - range);
      start.second = (nc.second - range);
      last.first = (nc.first + range);
      last.second = (nc.second + range);

      /*std::cout << "Start " << start.first << ":" << start.second;
      std::cout << " Last " << last.first << ":" << last.second << std::endl;*/
      remember = start.first;

      /*std::cout << "Map " << start.first << ":" << start.second;
      std::cout << " to " << last.first << ":" << last.second << std::endl;
      std::cout << "Player in " << nc.first << ":" << nc.second << std::endl;*/

      for (;start.second <= last.second; ++start.second)
      {
          for (; start.first <= last.first; ++start.first)
          {
              ptr = (*_map)[start];
              if (ptr && ptr->getType() == PLAYER)
              {
                pl = dynamic_cast<Player*>(ptr);
                dirs.push_back(static_cast<char>(pl->getDir()) + 48);
              }
              char c = ((ptr != NULL) ? (ptr->getType()) : (NONE));
              aff.push_back(((ptr != NULL) ? (ptr->getType()) : (NONE)));
          }
          start.first = (nc.first - range);
      }
    }
    ++it;
  }
  return aff + dirs;
}

/*
    Gen aléatoire :
  - Ne pas se tuer au spawn si besoin de détruire object
  - Essayer de faire des couloirs
*/
void	Gameplay::leftSort(int first, int last, int number, int nb)
{
  int	pivot;
  int	ok = 0;
  int	i = 0;

  if (number > 0)
    {
      number--;
      pivot = ((last - first) / (nb / 2));
      if (last - pivot < 0)
	{
	  while (!ok)
	    {
	      if (((*_map)[Coord(i % _map->width(), i / _map->height())])->getType() != PLAYER)
		{
		  _map->assign(*_itp, Coord(i % _map->width(), i / _map->height()));
		  (*_itp)->move(Coord(i % _map->width(), i / _map->height()));
		  ++_itp;
		  ok = 1;
		}
	      i++;
	    }
	}
      else
	{
	  _map->assign(*_itp, Coord((last - pivot) % _map->width(), (last - pivot) / _map->height()));
	  (*_itp)->move(Coord((last - pivot) % _map->width(), (last - pivot) / _map->height()));
	  ++_itp;
	}
      leftSort(first, last - pivot - 1, number, nb);
    }
}

void	Gameplay::rightSort(int first, int last, int number, int nb)
{
  int	pivot;
  int	ok = 0;
  int	i;
  int	map_size = (_map->width() * _map->height());

  if (number > 0)
    {
      number--;
      pivot = first + ((last - first) / (nb / 2));
      if (pivot >= map_size)
	{
	  i = map_size - 1;
	  while (!ok)
	    {
	      if (((*_map)[Coord(i % _map->width(), i / _map->height())])->getType() != PLAYER)
		{
		  _map->assign(*_itp, Coord(i % _map->width(), i / _map->height()));
		  (*_itp)->move(Coord(i % _map->width(), i / _map->height()));
		  ++_itp;
		  ok = 1;
		}
	      i--;
	    }
	}
      else
	{
	  _map->assign(*_itp, Coord(pivot % _map->width(), pivot / _map->height()));
	  (*_itp)->move(Coord(pivot % _map->width(), pivot / _map->height()));
	  ++_itp;
	}
      rightSort(pivot + 1, last, number, nb);
    }
}


void	Gameplay::littleSort(int nb_player)
{
  int	step;
  int	i;


  i = 0;

  if (nb_player == 1)
    {
      _map->assign(*_itp, Coord(_map->width() / 2, _map->height() / 2));
      (*_itp)->move(Coord(_map->width() / 2, _map->height() / 2)); // SEGFAULT
      return;
    }
  /*  step = (_map->width() * _map->height()) / ((nb_player - 1 > 0) ? nb_player - 1 : nb_player); // SALUT JE SUIS UN PANSEMENT*/
  step = (_map->width() * _map->height()) / ((nb_player - 1)); // SALUT JE SUIS UN PANSEMENT
  while (i < (_map->width() * _map->height()))
    {
      _map->assign(*_itp, Coord(i % _map->width(), i / _map->height()));
      (*_itp)->move(Coord(i % _map->width(), i / _map->height()));
      i += step;
      *_itp++;
    }
  _map->assign(*_itp, Coord(_map->width() - 1, _map->height() - 1));
  (*_itp)->move(Coord(_map->width() - 1, _map->height() - 1)); // SEGFAULT
}

void	Gameplay::placePlayer()
{
  int	map_size = _map->width() * _map->height();
  int	nb_player  = _ps.size();
  Coord c;
  int j = 0;

  _itp = _ps.begin();
  for (int i = 0; i < nb_player; i++)
  {
    c.first = i * 20;
    c.second = i * 20;
    for (j = 0; (*_map)[Coord(c.first + j, c.second + j)] != NULL ; j++);
    c.first += j;
    c.second += j;
    (*_itp)->move(c);
    (*_itp)->saveSpawn();
    _map->assign(NULL, c);
    _map->assign(*_itp, c);
    ++_itp;
  }
}

void Gameplay::save(const std::string &file)
{
  _map->save(file);
}

void Gameplay::load(const std::string &path)
{
  resetPlayers();
  _map->load(path);

  AElem *e;

  for (int i = 0; i < (_map->width() * _map->height()); i++)
  {
    e = (*_map)[Coord(i % _map->width(), i / _map->height())];
    if (e && e->getType() == PLAYER)
    {
      _ps.push_back(dynamic_cast<Player*>(e));
    }
  }
}

std::string Gameplay::getComposition() const
{
  int nbBox(0), nbWall(0), nbPl(0);
  std::stringstream stream;
  std::string final;
  AElem *e;

  nbPl = _ps.size();
  Coord start,end;

  start.first = 0;
  start.second = 0;
  end.first = _map->width();
  end.second = _map->height();
  for(;start.second < end.second; start.second++)
  {
    for(;start.first < end.first; start.first++)
    {
      e = (*_map)[start];
      if (e && e->getType() == BOX)
        ++nbBox;
      else if (e && e->getType() == WALL)
        ++nbWall;
    } 
    start.first = 0;
  }
  stream << nbPl << ":" << nbBox << ":" << nbWall;
  final = stream.str();
  return final;
}
