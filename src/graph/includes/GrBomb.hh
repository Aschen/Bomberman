#ifndef Bomb_HPP
#define Bomb_HPP

#include <AObject.hh>
#include <Texture.hh>
#include <glm/glm.hpp>
#include <Model.hh>
#include <Graph.hh>

namespace gdl {
class Bomb : public AObject
{
public:
    // Le model et l'init
    static  gdl::Texture texture;
    static  bool loadTexture();

private:
    // La texture utilisee pour le Bomb
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    // Le modele 3d du cube
    gdl::Model   _model;

    // AObject interface
public:
    Bomb(const glm::vec3 pos);
    ~Bomb(){}
    bool initialize();
    void update(const gdl::Clock &clock, gdl::Input &input);
    void draw(gdl::AShader &shader, const gdl::Clock &clock);
};
}
#endif // Bomb_HPP
