#ifndef Box_HH
#define Box_HH

#include <AObject.hh>
#include <Texture.hh>

namespace gdl {
class Box : public AObject
{
public:
    // La texture utilisee pour le cube
    static  gdl::Texture texture;
    static bool loadTexture();

private:   
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
