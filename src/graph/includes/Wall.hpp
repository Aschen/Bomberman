#pragma once

#include <AObject.hh>
#include <Texture.hh>

namespace gdl {
class Wall : public AObject
{
private:
    // La texture utilisee pour le Wall
    gdl::Texture _texture;
    // La geometrie du Wall
    gdl::Geometry _geometry;
    // La vitesse de deplacement du Wall
    float _speed;

public:
    Wall(const glm::vec3 &pos)
    {
        _position = pos;
    }
    virtual ~Wall()
    {}
    virtual bool initialize();
    // Ici le Wall bougera avec les fleches du clavier
    virtual void update(const gdl::Clock &clock, gdl::Input &input);
    virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
};
}
