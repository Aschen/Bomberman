#include "Player.hh"

Player::Player(int id, const std::string &name) : AElem(), _name(name), _id(id),_kills(0), _deaths(0)
{
	_d = DOWN;
	_links[Command::UP] = UP;
	_links[Command::DOWN] = DOWN;
	_links[Command::LEFT] = LEFT;
	_links[Command::RIGHT] = RIGHT;
}

Player::~Player()
{}

bool Player::move(const Coord &nc)
{
  _x = (nc.first < 0) ? 0 : nc.first;
  _y = (nc.second < 0) ? 0 : nc.second;
  return true;
}

void Player::die() const
{
  std::cout << "Die !" << std::endl;
}

void Player::takeDmg()
{
  ++_deaths;
  this->die();
}

char Player::getType() const
{
	return PLAYER;
}

int Player::id() const
{
	return _id;
}

int Player::kills() const
{
	return _kills;
}

void Player::kills(int score)
{
	_kills += score;
}

int Player::deaths() const
{
	return _deaths;
}

void Player::deaths(int score)
{
	_deaths += score;
}

std::string Player::name() const
{
	return _name;
}

void Player::setDir(const Command::Action act)
{
	_d = _links[act];
}

direction Player::getDir() const
{
	return _d;
}

void Player::saveSpawn()
{
	_spawn = Coord(_x, _y);
}

Coord Player::getSpawn() const
{
	return _spawn;
}
