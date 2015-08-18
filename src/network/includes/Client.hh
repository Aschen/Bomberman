#ifndef CLIENT_HH
#define CLIENT_HH

#include <cstdlib>
#include <unistd.h>

#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "Socket.hh"
#include "Network.hh"
#include "GameEngine.hh"
#include <Menu.hh>
#include <vector>
#include <Graph.hh>
#include <pthread.h>
#include <stdexcept>

//a supprimer:
#include <cmath>

class Client
{
private:
    Socket              *_socket;
    gdl::GameEngine     _engine;
    bool    			_play;
    bool                _canAskMap;
    bool                _canSendCmd;

public:
    Client(const std::string address, int port = 4242);
    ~Client(void);

    /* Fonctions principales */
private:
    void            run(void);
  int             initSelect(timeval &tv, fd_set *readfds, fd_set *writefds = NULL) const;
  void            handleSockets(void);
    void            askMap(void);
    bool            getPlayerEvent(void);

    /* Event selon les messages recu du serveur */
private:
    void            updateMap(Message &msg);
    void            sendSynchro(void);
    void            startGame(void);
    void            stopGame(void);
    void            updateCmd(void);
};

#endif // CLIENT_HH
