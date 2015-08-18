#ifndef Cursor_HH
#define Cursor_HH

#include <AObject.hh>
#include <Texture.hh>

namespace gdl {
class Cursor : public AObject
{
private:
    // La texture utilisee pour le cube
    gdl::Texture _texture;
    // La geometrie du cube
    gdl::Geometry _geometry;
    float x;
    float z;

public:
    Cursor(const glm::vec3 pos)
    {
        _position = pos;
    }
    ~Cursor()
    {}
    virtual bool initialize();
    void update(glm::vec3 pos);
    virtual void draw(gdl::AShader &shader, const gdl::Clock &clock);
};
}

#endif // Cursor_HH
