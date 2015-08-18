//
// Gameplay.cpp for - in /home/brunne_r/Links/bomberman
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Wed May  7 14:58:01 2014 brunne-r
// Last update Wed Jun 25 23:14:37 2014 Thibaut Sabot
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

bool  Gameplay::do_action(int id, Command::Action action)
{
  std::vector<Player*>::const_iterator it, end;
  Coord nc;
  AElem *a;
  bool b(false);

  it = _ps.begin();
  end = _ps.end();
  while (it < end)
  {
    if ((*it)->id() == id)
    {
      nc = (*it)->getCoord();
      if (action >= Command::UP && action <= Command::RIGHT)
      {
	if (_map->isFree(action, nc) || ((*_map)[nc])->getType() == NONE)
	  b = true;
	if (b)
	{
	  if ((*it)->move(nc))
	  {
	    (*it)->setDir(action);
	    _map->assign(NULL, (*it)->getCoord());
	    _map->assign(*it, nc);
	  }
	}
	      return b;
      }
      else if (action == Command::DBOMB)
	    {
	if (_map->isFree(Command::UP, nc))
	  ;// BOmB
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

static void  *runBomb(void *arg)
{
  Gameplay *g;

  g = reinterpret_cast<Gameplay *>(arg);
  g->manageBombs();
  return NULL;
}

void  Gameplay::run(void)
{
  pthread_t t;
  void *(*f)(void*);
  AElem *a;

  _ps[0]->move(Coord(50,50));
  _map->assign(_ps[0], Coord(50,50));
  f = runBomb;
  t = pthread_create(&t, NULL, f, (void*)this);
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
  int lastTime = time(NULL);


  pthread_exit(0);
  while (_ps.size() > 1)
  {
    lastTime = time(NULL) - lastTime;
    if (_bombs.size() > 0)
    {
      it = _bombs.begin();
      end = _bombs.end();
      while (it < end)
      {
	if ((*it)->dec(lastTime))
	{
	  (*it)->explode(_map);
	  delete *it;
	  _bombs.erase(it);
	  break;
	}
	else
	  ++it;
      }
    }
    else
      usleep(200);
  }
}

std::string Gameplay::getCharMap(int range, int idp)
{
  std::string aff;
  std::vector<Player*>::const_iterator it, end;
  Coord nc, start, last;
  AElem *ptr;

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
      for (;start.second <= last.second; ++start.second)
      {
      	for (; start.first <= last.first; ++start.first)
      	{
      	  ptr = (*_map)[start];
      	  char c = ((ptr != NULL) ? (ptr->getType()) : (NONE));
      	  aff.push_back(((ptr != NULL) ? (ptr->getType()) : (NONE)));
      	}
	      start.first = (nc.first - range);
      }
    }
    ++it;
  }
  return aff;
}
