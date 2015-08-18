#ifndef AOBJECT_HH
# define AOBJECT_HH

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <AShader.hh>
#include <Geometry.hh>

// La classe abstraite representant un objet avec sa position, sa rotation et son echelle
class AObject
{
protected:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

public:
    AObject();
    virtual ~AObject()
    {}
    virtual bool initialize();
    // La fonction update sert a gerer le comportement de l'objet
    virtual void update(gdl::Clock const &clock, gdl::Input &input)
    {}
    // La fonction draw sert a dessiner l'objet
    virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
    void translate(glm::vec3 const &v);
    void rotate(glm::vec3 const& axis, float angle);
    void scale(glm::vec3 const& scale);
    glm::mat4 getTransformation(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3 &position);
};

#endif // AOBJECT_HH
