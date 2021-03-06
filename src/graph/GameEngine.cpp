#include "GameEngine.hh"

namespace gdl {
GameEngine::GameEngine()
{}

GameEngine::~GameEngine()
{
    // N'oublions pas de supprimer les objets une fois le programme termine!
    for (size_t i = 0; i < _objects.size(); ++i)
	delete _objects[i];
}

bool GameEngine::initMenu()
{
    _objects.push_back(new Menu(glm::vec3(0, 0, 0)));
    _objects.push_back(new Cursor(glm::vec3(2.4, 1, 4)));
    for (std::vector<AObject*>::iterator i = _objects.begin(); i != _objects.end(); ++i)
    {
        if ((*i)->initialize() == false)
            return false;
    }
    return (true);
}

void GameEngine::receiveMap(const std::string &map, const std::vector<int> orientations)
{
    gdl::Player *pl;
    int iwall (0), ibox (0), ipl(0), ibomb(0), iflame(0), a(0);

    std::vector<int>::const_iterator it = orientations.begin();

    _objects.clear();
    for (int i = 0; i < map.length(); ++i) {
	switch (map[i]) {
	case BOX:
	    _lbox[ibox]->setPosition(glm::vec3(i % WIDTH, 0, i / WIDTH));
        ++ibox;
	    break;
	case BOMB:
        _lbomb[ibomb]->setPosition(glm::vec3(i % WIDTH, 0, i / WIDTH));
        ++ibomb;	    
	    break;
	case FLAMES:
        _lflame[iflame]->setPosition(glm::vec3(i % WIDTH, 0, i / WIDTH));
        ++iflame;	    
	    break;
	case WALL:
	    _lwall[iwall]->setPosition(glm::vec3(i % WIDTH, 0, i / WIDTH));
        ++iwall;
	    break;
	case PLAYER:
	    _lpl[ipl]->setPosition(glm::vec3(i % WIDTH, 0, i / WIDTH));
        _lpl[ipl]->setDirec(orientations[ipl]);
        if (i % WIDTH == WIDTH / 2 && i / WIDTH == HEIGHT / 2)
            _player = _lpl[ipl];
        ++ipl;
	    break;
    default:
	    break;
	}
    }
    // Push de tout les objets utilisés
    for (a = 0; a < ibox; a++)
        _objects.push_back(_lbox[a]);
    for (a = 0; a < iwall; a++)
        _objects.push_back(_lwall[a]);
    for (a = 0; a < ipl; a++)
        _objects.push_back(_lpl[a]);
    for (a = 0; a < ibomb; a++)
        _objects.push_back(_lbomb[a]);
    for (a = 0; a < iflame; a++)
        _objects.push_back(_lflame[a]);
}

bool GameEngine::initialize()
{

    _time = 0;
    if (!_context.start(1600, 1000, "Bomberman")) // on cree une fenetre
        throw std::runtime_error("Error when loading window.");
    // On active le test de profondeur d'OpenGL pour que les pixels que l'oeil ne voit pas ne
    // s'affichent pas
    glEnable(GL_DEPTH_TEST);
    // On cree un shader, petit programme permettant de dessiner nos objets a l'ecran
    if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) /* le fragment shader se charge de dessiner les pixels */
    || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) /* le vertex shader s'occupe de projeter les points sur l'ecran */
    || !_shader.build()) /* il faut ensuite compiler son shader */
        throw std::runtime_error("Error when loading shader.");
    // On place ensuite la camera (sa projection ainsi que sa transformation)
    glm::mat4 projection;
    glm::mat4 transformation;
    // La projection de la camera correspond a la maniere dont les objets vont etre dessine a l'ecran
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    // La transformation de la camera correspond a son orientation et sa position
    // La camera sera ici situee a la position 0, 10, 30 et regardera vers la position 0, 0, 0
    transformation = glm::lookAt(glm::vec3(0, 10, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // On doit toujours binder le shader avant d'appeler les methodes setUniform
    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);    
    return true;
}

void    GameEngine::allocObjects(int range, int nbPl)
{
    int i (0);

    std::cout << "Start Alloc" << std::endl;
    for (i = 0; i < range * range - 1; i++)
    {
        _lbox.push_back(new Box(glm::vec3(0,0,0)));
        _lwall.push_back(new Wall(glm::vec3(0,0,0)));
        _lbomb.push_back(new Bomb(glm::vec3(0,0,0)));
        _lflame.push_back(new Flames(glm::vec3(0,0,0)));
        _lbox[i]->initialize();
        _lwall[i]->initialize();
        _lbomb[i]->initialize();
        _lflame[i]->initialize();
    }
    std::cout << "Alloc and initialize BOX and WALL" << std::endl;
    for (i = 0; i < 4; i++)
    {
        _lpl.push_back(new Player(glm::vec3(0,0,0), DOWN, DEFAULT));
        _lpl[i]->initialize();
    }
    std::cout << "Alloc and initialize PLAYER" << std::endl;
}


bool GameEngine::updateMenu()
{
    Menu *m;
    Cursor *c;
    glm::mat4 transformation;
    glm::mat4 projection;
    bool state(true);

    _time += static_cast<float>(_clock.getElapsed()) * 10;
    _context.updateClock(_clock);
    _context.updateInputs(_input);
    m = dynamic_cast<Menu*>(_objects[0]);
    c = dynamic_cast<Cursor*>(_objects[1]);
    if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
    if (_input.getKey(SDLK_LEFT) && _time > 2)
    {        
        m->previousCursor();
        c->update(m->getCursorPosition());
        _time = 0;
    }
    else if (_input.getKey(SDLK_RIGHT) && _time > 2)
    {
        m->nextCursor();
        c->update(m->getCursorPosition());
        _time = 0;
    }
    else if (_input.getKey(SDLK_RETURN) && _time > 2)
    {
        _time = 0;
        if (m->nextMenu() == false)
            return (false);
        c->update(m->getCursorPosition());
    }
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    transformation = glm::lookAt(glm::vec3(0 , 11, 7), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);
    return (state);
}

bool GameEngine::update()
{
    glm::mat4 transformation;
    glm::mat4 projection;

    // Mise a jour des inputs et de l'horloge de jeu
    _context.updateClock(_clock);
    _context.updateInputs(_input);

    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    // Mise a jour des differents objets
    for (size_t i = 0; i < _objects.size(); ++i)
        _objects[i]->update(_clock, _input);
    // Mise à jour de la caméra (suivant le player)

    /// TMP
	transformation = glm::lookAt(glm::vec3(0 + _player->getPosition().x, 11, 7 + _player->getPosition().z),
				 glm::vec3(_player->getPosition().x, 0, _player->getPosition().z), glm::vec3(0, 1, 0));
//    transformation = glm::lookAt(glm::vec3(0, 11, 7), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);
    return true;
}

void GameEngine::draw()
{
    // On clear l'ecran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // pour utiliser un shader (pour que ce soit ce dernier qui dessine la geometrie) il faut le binder.
    // Un seul shader peut etre actif en meme temps
    _shader.bind(); // On dessine tous les objets composant la scene
    for (size_t i = 0; i < _objects.size(); ++i)
	_objects[i]->draw(_shader, _clock);
    // On met ensuite a jour l'ecran pour que ce que l'on a dessine s'affiche
    _context.flush();
}

int GameEngine::getKey(bool flag)
{
    _context.updateInputs(_input);
    if (_input.getKey(SDLK_UP, flag))
    {
        return UP;
    }
    else if (_input.getKey(SDLK_DOWN, flag))
    {
        return DOWN;
    }
    else if (_input.getKey(SDLK_LEFT, flag))
    {
        return LEFT;
    }
    else if (_input.getKey(SDLK_RIGHT, flag))
    {
        return RIGHT;
    }
    else if (_input.getKey(SDLK_ESCAPE, flag))
    {
        return ESC;
    }
    else if (_input.getKey(SDLK_SPACE, flag))
    {
        return SPACE;
    }
    return STAY;
}
}
