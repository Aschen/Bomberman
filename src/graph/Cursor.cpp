#include "Cursor.hh"

namespace gdl {
bool Cursor::initialize()
{
    // On charge la texture qui sera affichee sur chaque face du cube
    if (_texture.load("./assets/cursor.tga") == false)
    {
    std::cerr << "Cannot load the cursor texture" << std::endl;
	return (false);
    }
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    // Tres important, on n'oublie pas de build la geometrie pour envoyer ses informations a la carte graphique
    _geometry.build();
    return (true);
}

void Cursor::update(glm::vec3 pos)
{
    this->_position = pos;
}

void Cursor::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    (void)clock;
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre cube
    _geometry.draw(shader, getTransformation(this->_position, glm::vec3(-58, 0, -90), glm::vec3(0.5, 0.5, 0.5)), GL_QUADS);
}
}
