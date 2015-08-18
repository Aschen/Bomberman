#include "Client.hh"

pthread_mutex_t    mutex_cl = PTHREAD_MUTEX_INITIALIZER;

Client::Client(std::string address, int port)
    : _socket(new Socket(address, port))
{    
    _socket->start();

    std::cout << _socket->getState() << std::endl;


    handleSockets();
}

Client::~Client(void)
{
    delete _socket;
}


void Client::handleSockets(void)
{
    fd_set                    readfds;
    fd_set                    writefds;
    int                          fd_max;
    struct timeval         tv;
    Message               msg;
    bool                  play = true;
    pthread_t         thread;

    // On commece le thread pour demander la map tout les x temps

    while (play)
    {
        fd_max = initSelect(tv, &readfds, &writefds);
        if (select(fd_max, &readfds, NULL, NULL, &tv) == -1)
        {
            std::cout << "Select Error " << strerror(errno) << std::endl;
        }
        pthread_mutex_lock(&mutex_cl);
        if (FD_ISSET(_socket->get(), &writefds))
        {
            _socket->sendMsg();
        }


        if (FD_ISSET(_socket->get(), &readfds))
        {
            _socket->receiveMsg();
            std::cout << "SIze " << _socket->getReadQueueSize() << std::endl;

            pthread_mutex_unlock(&mutex_cl);
            while (_socket->getMessage(msg))
            {
                switch (Network::stringToCmd(msg.first))
                {
                case Network::SYN:
                    sendSynchro();
                    break;
                case Network::MAP:
                    updateMap(msg);
                    break;
                case Network::START:
                    beginGame(&thread);
                    break;
                case Network::END:
                    endGame(&thread);
                    break;
                    /* Probleme.. */
                default:
                    std::cout << "Default switch" << std::endl;
                    break;
                }
            }
        }
        pthread_mutex_unlock(&mutex_cl);
    }

    // On kill le thread de demande de map.


}

int Client::initSelect(timeval &tv, fd_set *readfds, fd_set *writefds)
{
    pthread_mutex_lock(&mutex_cl);
    int     fd_max = _socket->get();

    /* Timeout 4 secondes */
    tv.tv_sec = 0;
    tv.tv_usec = 10000;

    /* On prepare les champs de bits pour select */
    FD_ZERO(readfds);
    FD_SET(_socket->get(), readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_socket->get(), writefds);
    }
    pthread_mutex_unlock(&mutex_cl);
    return fd_max + 1;
}


void Client::updateMap(Message &msg)
{
    std::cout << "Le server nous demande d'update la map" << std::endl;
    std::cout << "On a reçu [" << msg.second << "]" << std::endl;

}


void Client::sendSynchro(void)
{
    pthread_mutex_lock(&mutex_cl);
    _socket->addMessage(Message(Network::cmdToString(Network::ACK), ""));
    std::cout << "Envoi du message de verification" << std::endl;
    pthread_mutex_unlock(&mutex_cl);
}



void Client::beginGame(pthread_t *thread)
{
    void* (*pVoid)(void *);

    std::cout << "le server nous demande de démarrer le jeux." << std::endl;

    pVoid=(void *(*)(void *))timeLoop;

    if (pthread_create(thread, NULL, pVoid, this) != 0)
    {
        std::cout << "y a une merde dans le thread" << std::endl;
    }
}


void Client::endGame(pthread_t *thread)
{
    std::cout << "le server nous demande de finir le jeux." << std::endl;
    if (pthread_cancel(*thread) != 0)
    {
        std::cout << "on a pas pu cancel le thread." << std::endl;
    }
}

void Client::askMap()
{
    pthread_mutex_lock(&mutex_cl);

    _socket->addMessage(Message(Network::cmdToString(Network::MAP), ""));
    pthread_mutex_unlock(&mutex_cl);
 }

void *Client::timeLoop(Client *client)
{
    while (true)
    {
        client->askMap();
        usleep(1000000);
    }
    return (NULL);

}



