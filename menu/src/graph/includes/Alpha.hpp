#pragma once

#include <AObject.hh>
#include <Texture.hh>

class Alpha : public AObject
{
private:
    // Le charactère utilisee
    gdl::Texture _texture;
    gdl::Geometry _geometry;

public:
    Alpha()
    {}
    virtual ~Alpha()
    {}
    virtual bool initialize(char *letter);
    virtual void update();
    virtual void draw(gdl::AShader &shader, gdl::Clock const &clock);
};
