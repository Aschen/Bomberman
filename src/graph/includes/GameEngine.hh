#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <Game.hh>
#include <SdlContext.hh>
#include <AObject.hh>
#include <BasicShader.hh>
#include <GrWall.hpp>
#include <GrPlayer.hpp>
#include <vector>
#include <Graph.hh>
#include <GrBox.hh>
#include <GrBomb.hh>
#include <GrFlames.hh>
#include <Menu.hh>
#include <Cursor.hh>

#include "Server.hh"


class Client;


namespace	gdl
{
class GameEngine : public Game
{
private:
    gdl::SdlContext         _context;
    gdl::Input              _input;
    std::vector<AObject*>   _objects;
    gdl::Player             *_player;
    gdl::Clock              _clock;
    gdl::BasicShader        _shader;
    float                   _time;
    std::vector<gdl::Box*>   _lbox;
    std::vector<gdl::Wall*>  _lwall;
    std::vector<gdl::Player*> _lpl;
    std::vector<gdl::Bomb*> _lbomb;
    std::vector<gdl::Flames*> _lflame;
public:
    gdl::Menu               *_menu;

public:
    GameEngine();
    virtual ~GameEngine();
    void receiveMap(const std::string &map, const std::vector<int> orientations);
    bool initMenu();
    bool updateMenu();

    // Game interface
public:
    bool    initialize();
    void    allocObjects(int range = SIDE / 2, int nbPl = 1);
    bool    update();
    void    draw();
    int     getKey(bool flag);

    gdl::Clock getClock() {
        return _clock;
    }
    gdl::BasicShader& getShader() {
        return _shader;
    }
};
}

#include "Client.hh"
#endif // GAMEENGINE_HH
