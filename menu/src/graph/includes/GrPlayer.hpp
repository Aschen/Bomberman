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
private:
    // La texture utilisee pour le player
    gdl::Texture _texture;
    // Le modele 3d du cube
    gdl::Model   _model;
    // La vitesse de deplacement du player
    float _speed;
    // La direction du player
    int     _direc;
    // L'état du player
    int     _state;

    // AObject interface
public:
    Player(const glm::vec3 pos, const int direc, const int state);
    ~Player(){}
    bool initialize();
    void update(const gdl::Clock &clock, gdl::Input &input);
    void draw(gdl::AShader &shader, const gdl::Clock &clock);
};
}
#endif // PLAYER_HPP
