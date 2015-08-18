#include <GrBomb.hh>

namespace gdl {
Bomb::Bomb(const glm::vec3 pos)
{
    // set l'échelle
    _scale = glm::vec3(0.0025, 0.0025, 0.0025);
    // la position
    _position = pos;
}

bool Bomb::initialize()
{
    // On charge le modèle 3d
    if (!_model.load("assets/bomb.fbx"))
    {
	std::cerr << "Cannot load model" << std::endl;
	return false;
    }
    if (!this->_model.setCurrentAnim(0, true))
    {
	std::cerr << "Cannot set animation" << std::endl;
	return (false);
    }
    return (true);
}

void Bomb::update(const gdl::Clock &clock, gdl::Input &input)
{
    // On multiplie par le temps ecoule depuis la derniere image pour que la vitesse ne depende pas de la puissance de l'ordinateur
    // On update la position et la rotation
}

void Bomb::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre model
    _model.draw(shader, getTransformation(_position, _rotation, _scale), clock.getElapsed());
}
}
