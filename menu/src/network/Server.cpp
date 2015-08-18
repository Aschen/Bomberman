#include "Server.hh"

Server::Server(int port)
{

    /*
     * Ici on s'auto initialise en attendant d'être appelé par le menu.
     * On créer plusieurs varibales, mais plus tard on les recuperera dans un objet MENU avec des gets.
*/



    int nb_joueur = 2;
    std::string path_de_la_map("maps/map1.map");
    int nb_ia = 2;

    /*
     *
     * A partir d'ici c'est normal.
     */


    _map = path_de_la_map;
    _nbPlayers = nb_joueur;
    _core = new Gameplay("toto");
    _socket = new Socket(port);
    _multiplayers = (_nbPlayers > 1) ? true : false;
    //_play = false;




    std::cout << "Creation serveur " << (_multiplayers ? (" multiplayers ") : (" local ")) << " avec " << _nbPlayers << " joueurs sur le port " << _socket->getPort() << std::endl;



    if (!_socket->start())
        exit(1);
    _socket->setOption(SO_REUSEADDR);

    std::cout << _socket->getState() << std::endl;

    run();
}

Server::~Server(void)
{
    delete(_core);
    /*
    for (std::vector<Server::Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        // Suppression des clients
        delete(*it);
    }
    delete _socket;
*/
}

int Server::initSelect(timeval &tv, fd_set *readfds, fd_set *writefds)
{
    int     fd_max = _socket->get();

    /* Timeout 4 secondes */
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    /* On prepare les champs de bits pour select */
    FD_ZERO(readfds);
    FD_SET(_socket->get(), readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_socket->get(), writefds);
    }
    FD_SET(0, readfds);
    for (unsigned int i = 0; i < _clients.size(); ++i)
    {
        FD_SET(_clients[i]->get(), readfds);
        if (writefds != NULL)
            FD_SET(_clients[i]->get(), writefds);
        if (fd_max < _clients[i]->get())
            fd_max = _clients[i]->get();
    }
    return fd_max + 1;
}

bool Server::eventServer(void)
{
    Socket          socket;

    /* On accepte la connection du nouveau client */
    if (_socket->acceptConnection(socket) == false)
    {
        std::cerr << _socket->getError() << std::endl;
        return false;
    }
    _clients.push_back(new Server::Client(socket));
    std::cout << "on enregistrer un nouveau client (non confirmé)" << std::endl;
    std::cout << "On demande la confirmation" << std::endl;
    /* Demande de confirmation du client */
    _clients.back()->addMessage(Message(Network::cmdToString(Network::SYN), ""));


    /* Envoi de la map */
   // _clients.back()->addMessage(Message(Network::cmdToString(Network::MAP), _map));

    /* Envoi du message au client */
   /* while (_clients.back()->sendMsg(socket.get()))
        ;*/
    return true;
}

bool Server::eventClients(fd_set *readfds, fd_set *writefds)
{
    Message         msg;

    /* On parcours tout les clients déja connectés */
    for (std::vector<Server::Client*>::iterator it = _clients.begin(); it != _clients.end() ;)
    {
        /* Si il y a quelque chose à lire sur la socket*/
        if (FD_ISSET((*it)->get(), readfds))
        {
            /* Si le client s'est deconnecté */
            if ((*it)->receiveMsg() == 0)
            {
                delete(*it);
                _clients.erase(it);
                it = _clients.begin();
            }
            else
            {
                /* On récupère le message */
                while ((*it)->getMessage(msg))
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
                    default:
                        std::cout << "Default switch " << std::endl;
                        break;
                    }
                }
            }
        }
        /* Si on peut ecrire sur la socket */
        if (FD_ISSET((*it)->get(), writefds))
        {
            while ((*it)->sendMsg())
                ;
        }
        if (it != _clients.end())
            ++it;
    }
    return true;
}

bool Server::eventTerminal()
{
    char buf[500];
    int r;
    std::string str;

    memset(buf, 0, 500);
    r = read(0, buf, 500);
    buf[r - 1] = 0;
    str = buf;

    if (str == "end")
    {
        sendMessageAllClients(Network::END, "");
    }
    return (true);
}

void Server::handleSockets(void)
{
}

void Server::run(void)
{
    fd_set                    readfds;
    fd_set                    writefds;
    int                          fd_max;
    struct timeval            tv;
    bool run = true;

    while (run)
    {
        /*  Preparation et lancement de select() */
        fd_max = initSelect(tv, &readfds, &writefds);
        if (select(fd_max, &readfds, NULL, NULL, &tv) == -1)
        {
            std::cout << "Select Error " << strerror(errno) << std::endl;
        }
        else
        {
            /* Si un nouveau client essaye de se connecter */
            if (FD_ISSET(_socket->get(), &readfds))
            {
                eventServer();
            }
            if (FD_ISSET(0, &readfds))
            {
                eventTerminal();
            }
            /* On regarde si les clients nous envoies des infos */
            eventClients(&readfds, &writefds);
        }

        gameCanStart();


        if (_play)
        {

        }
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


bool Server::sendMessageAllClients(Network::cmd cmd, const std::string &msg)
 {
    std::cout << "on dit a tous les clients que cela commence" << std::endl;
    for (std::vector<Server::Client *>::iterator it = _clients.begin() ; it != _clients.end() ; ++it)
    {
        (*it)->addMessage(Message(Network::cmdToString(cmd), msg));
    }
    return (true);
}

void Server::gameCanStart()
{
    bool check;

    check = true;
    if (_play == false && _clients.size() == _nbPlayers)
    {
        for (std::vector<Server::Client *>::iterator it = _clients.begin() ; it != _clients.end() ; ++it)
        {
            if ((*it)->isVerified() == false)
                check = false;
        }
        if (check == true)
        {
            _play = true;
            int i = 1;
            std::stringstream ss;


            std::cout << "Tous les joueurs sont connectés et vérifiés." << std::endl;
            // On ajoute tous les players dans le gamePlay.
            for (std::vector<Server::Client *>::iterator it = _clients.begin() ; it != _clients.end() ; ++it)
            {
                ss << "name[" << i << "]";
                _core->addPlayer((*it)->get(), ss.str());
                i++;
            }
            _core->run();
            sendMessageAllClients(Network::START, "");
        }
    }
}


void Server::sendMapClient(Server::Client *client)
{
    std::string charmap;

    charmap = _core->getCharMap(3, client->get());
    client->addMessage(Message(Network::cmdToString(Network::MAP), charmap));
}
