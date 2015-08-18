#include <AObject.hh>

AObject::AObject() :
    _position(0, 0, 0), // On initialise la position a 0
    _rotation(0, 0, 0), // pareil pour la rotation
    _scale(1, 1, 1) // l'echelle est mise a 1
{
}

// La fonction initialize charge l'objet ou le construit
bool AObject::initialize()
{
    return (true);
}

void AObject::translate(glm::vec3 const &v)
{
    _position += v;
}

void AObject::rotate(glm::vec3 const& axis, float angle)
{
    _rotation += axis * angle;
}

void AObject::scale(glm::vec3 const& scale)
{
    _scale *= scale;
}

// GET et SET
glm::mat4 AObject::getTransformation(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) const
{
    glm::mat4 transform(1); // On cree une matrice identite
    // On effectue ensuite la translation
    transform = glm::translate(transform, position);
    // On applique ensuite les rotations selon les axes x, y et z
    transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
    // Et pour finir, on fait la mise a l'echelle
    transform = glm::scale(transform, scale);
    return (transform);
}

glm::vec3 AObject::getPosition() const
{
    return _position;
}

void AObject::setPosition(const glm::vec3 &position)
{
    _position = position;
}
