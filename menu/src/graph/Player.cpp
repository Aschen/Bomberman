#include <GrPlayer.hpp>

namespace gdl {
Player::Player(const glm::vec3 pos, const int direc, const int state)
{
    // set l'échelle
    _scale = glm::vec3(0.002, 0.002, 0.002);
    // Set la vitesse
    _speed = 10.0f;
    // la direction
    _direc = direc;
    // l'état
    _state = state;
    // la position
    _position = pos;
}

bool Player::initialize()
{
    // On charge le modèle 3d
    if (!_model.load("assets/marvin.fbx"))
    {
        std::cerr << "Cannot load model" << std::endl;
        return false;
    }
    // On découpe les animations
    // START
    if (!this->_model.createSubAnim(0, "start", 0, 40))
    {
        std::cerr << "Cannot create animation 'start'" << std::endl;
        return (false);
    }
    // RUN
    if (!this->_model.createSubAnim(0, "run", 40, 54))
    {
        std::cerr << "Cannot create animation 'run'" << std::endl;
        return (false);
    }
    // STOP
    if (!this->_model.createSubAnim(0, "stop", 54, 100))
    {
        std::cerr << "Cannot create animation 'stop'" << std::endl;
        return (false);
    }
    // On set l'animation
    if (!this->_model.setCurrentSubAnim("run", true))
    {
        std::cerr << "Cannot set animation" << std::endl;
        return (false);
    }
    return (true);
}

void Player::update(const gdl::Clock &clock, gdl::Input &input)
{
    // On multiplie par le temps ecoule depuis la derniere image pour que la vitesse ne depende pas de la puissance de l'ordinateur
    // On update la position et la rotation
    if (input.getKey(SDLK_UP))
    {
        translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
        switch (_direc) {
        case LEFT:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case DOWN:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        default:
            break;
        }
        _direc = UP;
    }
    if (input.getKey(SDLK_DOWN))
    {
        translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
        switch (_direc) {
        case LEFT:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case UP:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        default:
            break;
        }
        _direc = DOWN;
    }
    if (input.getKey(SDLK_LEFT))
    {
        translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
        switch (_direc) {
        case DOWN:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        case UP:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        default:
            break;
        }
        _direc = LEFT;
    }
    if (input.getKey(SDLK_RIGHT))
    {
        translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
        switch (_direc) {
        case DOWN:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case LEFT:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        case UP:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        default:
            break;
        }
        _direc = RIGHT;
    }
}

void Player::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre model
    _model.draw(shader, getTransformation(_position, _rotation, _scale), clock.getElapsed());
}
}
