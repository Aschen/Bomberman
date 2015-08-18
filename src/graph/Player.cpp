#include <GrPlayer.hpp>

namespace gdl {

Model Player::model;

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
    // la direction précédente
    _prevDir = DOWN;
}

bool gdl::Player::loadModel()
{
    static bool first = true;

    if (!first)
        return true;
    std::cout << "Loading 3D model..." << std::endl;
    if (Player::model.load("assets/marvin.fbx") == false)
    {
        std::cerr << "Cannot load the model" << std::endl;
    }
    first = false;
    return true;
}

bool Player::initialize()
{
    // On charge le modèle 3d
    loadModel();
    // On découpe les animations
    // START
    if (!this->model.createSubAnim(0, "start", 0, 40))
    {
        std::cerr << "Cannot create animation 'start'" << std::endl;
        return (false);
    }
    // RUN
    if (!this->model.createSubAnim(0, "run", 40, 54))
    {
        std::cerr << "Cannot create animation 'run'" << std::endl;
        return (false);
    }
    // STOP
    if (!this->model.createSubAnim(0, "stop", 54, 100))
    {
        std::cerr << "Cannot create animation 'stop'" << std::endl;
        return (false);
    }
    // On set l'animation
    if (!this->model.setCurrentSubAnim("run", true))
    {
        std::cerr << "Cannot set animation" << std::endl;
        return (false);
    }
    return (true);
}

void Player::update(const gdl::Clock &clock, gdl::Input &input)
{
    // On update la rotation en fonction de la direction précédente
    switch (_prevDir) {
    case DOWN:
        switch (_direc) {
        case LEFT:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case UP:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        default:
            break;
        }
        break;
    case UP:
        switch (_direc) {
        case LEFT:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case DOWN:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        default:
            break;
        }
        break;
    case LEFT:
        switch (_direc) {
        case UP:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        case RIGHT:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        case DOWN:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        default:
            break;
        }
        break;
    case RIGHT:
        switch (_direc) {
        case UP:
            rotate(glm::vec3(0, 1, 0), 90);
            break;
        case LEFT:
            rotate(glm::vec3(0, 1, 0), 180);
            break;
        case DOWN:
            rotate(glm::vec3(0, 1, 0), -90);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    _prevDir = _direc;
}

void Player::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre model
    model.draw(shader, getTransformation(_position, _rotation, _scale), clock.getElapsed());
}

int Player::getDirec() const
{
    return _direc;
}

void Player::setDirec(const int dir)
{
    _direc = dir;
}

int Player::getPrevDirec() const
{
    return _prevDir;
}

void Player::setPrevDirec(const int dir)
{
    _prevDir = dir;
}
}
