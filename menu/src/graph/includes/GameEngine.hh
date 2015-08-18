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
public:
    gdl::Menu               *_menu;

public:
    GameEngine();
    virtual ~GameEngine();
    bool receiveMap(const std::string &map, const std::vector<int> orientations);
    bool initMenu();
    bool updateMenu();

    // Game interface
public:
    bool initialize();
    void allocObjects(int range = SIDE / 2, int nbPl = 1);
    //bool update(std::string map, std::vector<int> orientations);
    bool update();
    void draw();
    gdl::Clock getClock() {
        return _clock;
    }
    gdl::BasicShader& getShader() {
        return _shader;
    }
};
}

#endif // GAMEENGINE_HH