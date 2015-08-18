//
// ABonus.hh for Abonus in /home/sabot_t/rendu/cpp_bomberman
//
// Made by Thibaut Sabot
// Login   <sabot_t@epitech.net>
//
// Started on  Wed May  7 11:51:17 2014 Thibaut Sabot
// Last update Wed May  7 15:37:16 2014 brunne-r
//

#ifndef ABONUS_H
# define ABONUS_H

class	ABonus
{
public:
  typedef enum	e_bonus
    {
      BOMB_PLUS,
      RANGE_PLUS,
      SPEED_PLUS
    }		Bonus;
private:
  Bonus		_type;

public:
  virtual void	doBonus(const AElem &player) = 0;
};

#endif /* !ABONUS_H */
