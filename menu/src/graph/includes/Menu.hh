#ifndef Menu_HH
#define Menu_HH

#include <AObject.hh>
#include <Texture.hh>

namespace gdl {

typedef enum face
{

}face;

class Menu : public AObject
{
private:
    // La texture utilisee pour le cube
    gdl::Texture _texture;
    std::string  _strTexture[6];
    // La geometrie du cube
    gdl::Geometry _geometry;
    std::vector<std::pair<glm::vec3, int> > _coordonee[6];
    int _idMenu;
    int _idCursor;

public:
    Menu(const glm::vec3 pos)
    {
        _position = pos;
    }
    ~Menu()
    {}
    virtual bool initialize();
    virtual void update(const gdl::Clock &clock, gdl::Input &input);
    virtual void draw(gdl::AShader &shader, const gdl::Clock &clock);
    void nextCursor();
    bool nextMenu();
    void previousCursor();
    glm::vec3 getCursorPosition();
};
}

#endif // Menu_HH
