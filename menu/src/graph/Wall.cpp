#include <GrWall.hpp>

namespace gdl {
bool Wall::initialize()
{
    _speed = 10.0f;
    // On charge la texture qui sera affichee sur chaque face du Wall
    if (_texture.load("./assets/texture.tga") == false)
    {
	std::cerr << "Cannot load the wall texture" << std::endl;
	return (false);
    }
    // On push les vertices d une premiere face
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z + 0.5));
    // Les UVs d'une premiere face
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    // ETC ETC
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z - 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z + 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z - 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, 0.5, _position.z + 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z - 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + 0.5, -0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z + 0.5));
    _geometry.pushVertex(glm::vec3(_position.x + -0.5, -0.5, _position.z - 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    // Tres important, on n'oublie pas de build la geometrie pour envoyer ses informations a la carte graphique
    _geometry.build();
    return (true);
}

void Wall::update(gdl::Clock const &clock, gdl::Input &input)
{
    /// TODO : Translate par rapport au déplacement du player
    // On multiplie par le temps ecoule depuis la derniere image pour que la vitesse ne depende pas de la puissance de l'ordinateur
//        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
}

void Wall::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    (void)clock;
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre Wall
    _geometry.draw(shader, getTransformation(_position, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), GL_QUADS);
}
}
