#include <Alpha.hpp>

bool Alpha::initialize(char *letter)
{
    // On charge la texture qui sera affichee
    if (_texture.load(letter) == false)
    {
        std::cerr << "Cannot load " << letter << " texture!" << std::endl;
        return (false);
    }
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.build();
    return (true);
}

void Alpha::update()
{
    translate(this->position);
}

void Alpha::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(glm::vec3(5, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), GL_QUADS);
}
