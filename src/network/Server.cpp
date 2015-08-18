#include "Server.hh"

Server::Server(int port, int nbPlayer) : _nbPlayers(nbPlayer), _play(false), _run(true), _socket(new Socket(port)), _core(new Gameplay("bombermap"))
{
    std::cout << "Creation serveur " << " avec " << _nbPlayers << " joueurs." << std::endl;
    std::cout << "Rejoignez " << _socket->getRemoteIp() << ":" << _socket->getPort() << " pour participer !" << std::endl;
    if (!_socket->start())
        throw std::runtime_error(_socket->getError());

    _socket->setOption(SO_REUSEADDR);

    run();
}

Server::~Server(void)
{

    delete _core;
    for (unsigned int i = 0; i < _clients.size(); i++)
    {
        delete(_clients[i]);
    }
    delete _socket;
}

void Server::eventTerminal(void)
{
    char        buf[128] = {0};

    if (read(0, buf, 127) > 0)
    {
        std::string cmd = buf;
        if (cmd == "exit\n")
        {
            std::cout << "Arrêt du serveur." << std::endl;
            sendMessageAllClients(Network::END, "ENDGAME");
            _run = false;
        }
    }
}

int Server::initSelect(timeval &tv, fd_set *readfds, fd_set *writefds) const
{
    int     fd_max = _socket->get();

    /* Timeout 4 secondes */
    tv.tv_sec = 0;
    tv.tv_usec = 400;

    /* On prepare les champs de bits pour select */
    FD_ZERO(readfds);
    FD_SET(_socket->get(), readfds);
    FD_SET(0, readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_socket->get(), writefds);
    }
    for (unsigned int i = 0; i < _clients.size(); i++)
    {
        FD_SET(_clients[i]->get(), readfds);
        if (writefds != NULL)
            FD_SET(_clients[i]->get(), writefds);
        if (fd_max < _clients[i]->get())
            fd_max = _clients[i]->get();
    }
    return fd_max + 1;
}

void Server::handleSockets(void)
{
    fd_set                    readfds;
    fd_set                    writefds;
    int                          fd_max;
    struct timeval            tv;

    /*  Preparation et lancement de select() */
    fd_max = initSelect(tv, &readfds, &writefds);
    if (select(fd_max, &readfds, NULL, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + strerror(errno));
    }
    else
    {
        /* Si une commande est tapée en console */
        if (FD_ISSET(0, &readfds))
            eventTerminal();
        /* Si un nouveau client essaye de se connecter */
        if (FD_ISSET(_socket->get(), &readfds))
            eventServer();
        /* On regarde si les clients nous envoies des infos */
        eventClients(&readfds, &writefds);
    }
}

void Server::eventServer(void)
{
    Socket          socket;

    /* On accepte la connection du nouveau client */
    if (_socket->acceptConnection(socket) == false)
    {
        throw std::runtime_error(_socket->getError());
    }
    _clients.push_back(new Server::Client(socket));
    /* Demande de confirmation du client */
    _clients.back()->addMessage(Message(Network::cmdToString(Network::SYN), ""));
}

void Server::eventClients(fd_set *readfds, fd_set *writefds)
{
    std::vector<Server::Client*>::iterator  it = _clients.begin();
    Message                                 msg;

    /* On parcours tout les clients déja connectés */
    while (it < _clients.end())
    {
        /* Si on peut ecrire sur la socket */
        if (FD_ISSET((*it)->get(), writefds))
        {
            (*it)->sendMsg();
        }
        /* Si il y a quelque chose à lire sur la socket*/
        if (FD_ISSET((*it)->get(), readfds))
        {
            /* Si le client s'est deconnecté */
            if ((*it)->receiveMsg() == 0)
            {
                std::cout << "Client " << (*it)->get() << " lost connection." << std::endl;
                delete(*it);
                _clients.erase(it);
                it = _clients.begin();
            }
            else
            {
                /* On récupère le message */
                while (_clients.size() > 0 && (*it)->getMessage(msg))
                {
                    switch (Network::stringToCmd(msg.first))
                    {
                    case Network::ACK:
                        if ((*it)->isVerified() == false)
                            (*it)->setVerified(true);
                        break;
                    case Network::MAP:
                        sendMapClient(*it);
                        break;
                    case Network::END:
//                        std::cout << "Le client " << (*it)->get() << " recoit END" << std::endl;
                        delete(*it);
                        _clients.erase(it);
                        it = _clients.begin();
                        break;
                    case Network::UP:
//                        std::cout << "Joueur " << (*it)->get() << " appuie UP" << std::endl;
                        receiveClientAction(*it, Command::UP);
                        break;
                    case Network::DOWN:
//                        std::cout << "Joueur " << (*it)->get() << " appuie DOWN" << std::endl;
                        receiveClientAction(*it, Command::DOWN);
                        break;
                    case Network::LEFT:
//                        std::cout << "Joueur " << (*it)->get() << " appuie LEFT" << std::endl;
                        receiveClientAction(*it, Command::LEFT);
                        break;
                    case Network::RIGHT:
//                        std::cout << "Joueur " << (*it)->get() << " appuie RIGHT" << std::endl;
                        receiveClientAction(*it, Command::RIGHT);
                        break;
                    case Network::DBOMB:
//                        std::cout << "Joueur " << (*it)->get() << " appuie SPACE" << std::endl;
                        receiveClientAction(*it, Command::DBOMB);
                        break;
                    default:
                        std::cout << "Default switch " << std::endl;
                        break;
                    }
                }
            }
        }
        /* Si le client peut envoyer la prochaine commande */
        ++it;
    }
}

void Server::run(void)
{
    while (_run)
    {
        handleSockets();
        if (gameCanStart())
        {
            initGame();
        }
        if (_play)
        {
            _core->manageBombs();
            if (_clients.size() == 0)
                _run = false;
        }
    }
    sendMessageAllClients(Network::END, "ENDGAME");
}

void Server::sendMessageAllClients(Network::cmd cmd, const std::string &msg) const
 {
    std::vector<Server::Client *>::const_iterator it = _clients.begin();

    while (it < _clients.end())
    {
        (*it)->addMessage(Message(Network::cmdToString(cmd), msg));
        ++it;
    }
}

bool Server::gameCanStart(void) const
{
    std::vector<Server::Client *>::const_iterator it = _clients.begin();

    if (_play == false && _clients.size() == _nbPlayers)
    {
        while (it < _clients.end())
        {
            if ((*it)->isVerified() == false)
            {
                return false;
            }
            ++it;
        }
        return true;
    }
    return false;
}


void Server::sendMapClient(Server::Client *client)
{
    std::string charmap;

    charmap = _core->getCharMap(12, client->get());
    client->addMessage(Message(Network::cmdToString(Network::MAP), charmap));
}

void Server::receiveClientAction(Server::Client *client, Command::Action action)
{
    if (_play)
        _core->do_action(client->get(), action);
    client->addMessage(Message(Network::cmdToString(Network::ACK), "CMD_ACK"));
}

void Server::initGame(void)
{
    std::vector<Server::Client *>::iterator it = _clients.begin();
    std::stringstream                       ss;

    _play = true;

    std::cout << "Tous les joueurs sont connectés et vérifiés." << std::endl;

    // On ajoute tous les players dans le gamePlay.
    while (it < _clients.end())
    {
        ss.str("");
        ss << " name[" << (*it)->get() << "]";
        _core->addPlayer((*it)->get(), ss.str());
        ++it;
    }
    std::cout << "--------------" << std::endl;

    _core->run();
    _core->dump();
    sendMessageAllClients(Network::START, "START");
}

void Server::sendCmdAck(Server::Client *client) const
{
    unsigned int  diff;

    std::cout << "Last cmd receive at " << client->getLastCmdTime() << " time now " << Time::getMicroTimestamp() << std::endl;
    diff = Time::getMicroTimestamp() - client->getLastCmdTime();
    std::cout << "Diff " << diff << std::endl;
    if (diff > 100000 && client->getLastCmdTime() != 0)
    {
        std::cout << "Client " << client->get() << " can send another command" << std::endl;
        client->addMessage(Message(Network::cmdToString(Network::ACK), "ACK"));
        client->setLastCmdTime(0);
    }
}

/******************************/
/**   Server::Client         **/
/******************************/
Server::Client::Client(Socket &socket)
    : Socket(socket.get(), socket.getRemoteIp()), _verified(false)
{
    std::cout << "Nouveau client n°" << get() << " connecté depuis " << getRemoteIp() << std::endl;
}

Server::Client::~Client(void)
{
    std::cout << "Client n°" << get() << " deconnecté" << std::endl;
    stop();
}

bool Server::Client::isVerified(void) const
{
    return _verified;
}

void Server::Client::setVerified(bool verified)
{
    std::cout << "Client n°" << get() << " vérifié" << std::endl;
    _verified = verified;
}


unsigned int Server::Client::getLastCmdTime() const
{
    return _lastCmdTime;
}


void Server::Client::setLastCmdTime(unsigned int time)
{
    _lastCmdTime = time;
}

