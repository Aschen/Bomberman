#ifndef Flames_HPP
#define Flames_HPP

#include <AObject.hh>
#include <Texture.hh>
#include <glm/glm.hpp>
#include <Graph.hh>

namespace gdl {
class Flames : public AObject
{
private:
    // La texture utilisee pour les flames
    gdl::Texture _texture;
    // La geometrie du cube
    gdl::Geometry _geometry;

    // AObject interface
public:
    Flames(const glm::vec3 &pos)
    {
        _position = pos;
    }
    ~Flames(){}
    bool initialize();
    void update(const gdl::Clock &clock, gdl::Input &input);
    void draw(gdl::AShader &shader, const gdl::Clock &clock);
};
}
#endif // Flames_HPP
