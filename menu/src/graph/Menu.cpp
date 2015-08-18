#include "Menu.hh"

namespace gdl {
bool Menu::initialize()
{
    _idMenu = 0;
    _idCursor = 4;
    _strTexture[0] = "./assets/menu.tga";
    _strTexture[1] = "./assets/network.tga";
    _strTexture[2] = "./assets/Options.tga";
    _strTexture[3] = "./assets/escap.tga";
    _strTexture[4] = "./assets/menu.tga";
    _strTexture[5] = "./assets/SelectionMode.tga";
    // On charge la texture qui sera affichee sur chaque face du cube
    if (_texture.load("./assets/menu.tga") == false)
    {
    std::cerr << "Cannot load the menu texture" << std::endl;
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
    _coordonee[0].push_back(std::pair<glm::vec3, int> (glm::vec3(2,1,2), 1));
    _coordonee[0].push_back(std::pair<glm::vec3, int> (glm::vec3(3.4,1,2), 2));
    _coordonee[0].push_back(std::pair<glm::vec3, int> (glm::vec3(1.7,1,4.4), 3));
    _coordonee[0].push_back(std::pair<glm::vec3, int> (glm::vec3(3.1,1,4.4), 4));
    _coordonee[0].push_back(std::pair<glm::vec3, int> (glm::vec3(2.4,1,4), 5));
    _coordonee[1].push_back(std::pair<glm::vec3, int> (glm::vec3(-4,1.3,-1.7), 0));

    _coordonee[1].push_back(std::pair<glm::vec3, int> (glm::vec3(-2,1.3,1), -1));

    _coordonee[1].push_back(std::pair<glm::vec3, int> (glm::vec3(6.6,1,5.6), 0));
    _coordonee[2].push_back(std::pair<glm::vec3, int> (glm::vec3(6.6,1,5.6), 0));
    _coordonee[3].push_back(std::pair<glm::vec3, int> (glm::vec3(6.6,1,5.6), 0));
    _coordonee[4].push_back(std::pair<glm::vec3, int> (glm::vec3(-4,1.3,-1.7), 0));
    _coordonee[4].push_back(std::pair<glm::vec3, int> (glm::vec3(6.6,1,5.6), 0));
    _coordonee[5].push_back(std::pair<glm::vec3, int> (glm::vec3(-4,1.3,-1.7), 0));
    _coordonee[5].push_back(std::pair<glm::vec3, int> (glm::vec3(6.6,1,5.6), 0));
    return (true);
}

void Menu::update(const gdl::Clock &clock, gdl::Input &input)
{

}

void Menu::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
    (void)clock;
    // On bind la texture pour dire que l'on veux l'utiliser
    _texture.bind();
    // Et on dessine notre cube
    _geometry.draw(shader, getTransformation(glm::vec3(0, 0, 0), glm::vec3(-58, 0, -90), glm::vec3(16, 20, 17)), GL_QUADS);
}

void Menu::nextCursor()
{
    _idCursor++;
    if (_idCursor >= _coordonee[_idMenu].size())
        _idCursor = 0;
}

void Menu::previousCursor()
{
    _idCursor--;
    if (_idCursor < 0)
        _idCursor = _coordonee[_idMenu].size() - 1;
}

glm::vec3 Menu::getCursorPosition()
{
    return _coordonee[_idMenu][_idCursor].first;
}

bool Menu::nextMenu()
{
    if (_idMenu == 0 && _idCursor == 3)
        return (false);
    if (_coordonee[_idMenu][_idCursor].second >= 0)
    {
        _idMenu = _coordonee[_idMenu][_idCursor].second;
        _idCursor = 0;
        if (_texture.load(_strTexture[_idMenu]) == false)
        {
            std::cerr << "Cannot load the menu texture" << std::endl;
            return (false);
        }
    }
    //else alpha
    return (true);
}

}

