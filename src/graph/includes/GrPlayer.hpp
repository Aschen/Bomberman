#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <AObject.hh>
#include <Texture.hh>
#include <glm/glm.hpp>
#include <Model.hh>
#include <Graph.hh>

namespace gdl {
class Player : public AObject
{
public:
    // Le model et l'init
    static  gdl::Model model;
    static bool loadModel();

private:
    // La texture utilisee pour le player
    gdl::Texture _texture;
    // La vitesse de deplacement du player
    float _speed;
    // La direction du player
    int     _direc;
    // La direction précédente
    int     _prevDir;
    // L'état du player
    int     _state;

    // AObject interface
public:
    Player(const glm::vec3 pos, const int direc, const int state);
    ~Player(){}
    bool initialize();
    void update(const gdl::Clock &clock, gdl::Input &input);
    void draw(gdl::AShader &shader, const gdl::Clock &clock);
    int     getDirec() const;
    void    setDirec(const int dir);
    int     getPrevDirec() const;
    void    setPrevDirec(const int dir);
};
}
#endif // PLAYER_HPP
