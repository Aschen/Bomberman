#ifndef Box_HH
#define Box_HH

#include <AObject.hh>
#include <Texture.hh>

namespace gdl {
class Box : public AObject
{
private:
    // La texture utilisee pour le cube
    gdl::Texture _texture;
    // La geometrie du cube
    gdl::Geometry _geometry;

public:
    Box(const glm::vec3 pos)
    {
        _position = pos;
    }
    ~Box()
    {}
    virtual bool initialize();
    virtual void update(const gdl::Clock &clock, gdl::Input &input);
    virtual void draw(gdl::AShader &shader, const gdl::Clock &clock);
};
}

#endif // Box_HH
