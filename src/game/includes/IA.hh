#ifndef IA_HH
#define IA_HH

#include "Player.hh"
#include "Maps.hh"
#include "Command.hh"

class IA
{
private:

public:
    static Command::Action          getAction(const Map &map, const std::vector<Player*>::iterator _itp, int playerId);

private:
    static bool                     dropBomb(const Map &map, int playerId);
    static Coord                    &findPlayer(const Map &map, int playerId);

};

#endif // IA_HH
