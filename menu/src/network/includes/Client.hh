#ifndef CLIENT_HH
#define CLIENT_HH

#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "Socket.hh"
#include "Network.hh"
#include <GameEngine.hh>
#include "GameEngine.hh"
#include <Menu.hh>
#include <vector>
#include <Graph.hh>
#include <pthread.h>



class Client
{
private:
    Socket              *_socket;
    gdl::GameEngine     _engine;

public:
    Client(std::string address, int port = 4242);
    ~Client(void);
    void         askMap();

private:
    int             initSelect(timeval &tv, fd_set *readfds, fd_set *writefds = NULL);
    void            handleSockets(void);
    void            updateMap(Message &msg);
    void            sendSynchro(void);
    void            beginGame(pthread_t *thread);
    void            endGame(pthread_t *thread);


static void            *timeLoop(Client  *);

};

#endif // CLIENT_HH
