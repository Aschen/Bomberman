#ifndef SERVER_HH
# define SERVER_HH

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <sys/select.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include "Socket.hh"
#include "Network.hh"
#include "Gameplay.hh"
#include "Command.hh"
#include "Maps.hh"
#include "Time.hh"

class   Server
{
public:
    const static int                PORT = 1337;

/*  Nested Classe pour gérer les différents clients se connectant au serveur  */
public:
    class   Client : public Socket
    {
    private:
        bool            _verified;
        unsigned int          _lastCmdTime;

    public:
        Client(Socket &socket);
        ~Client(void);

    public:
        bool            isVerified(void) const;
        void            setVerified(bool verified);
        unsigned int          getLastCmdTime(void) const;
        void            setLastCmdTime(unsigned int time);
    };

private:
    unsigned int                        _nbPlayers;
    bool                                _play;
    bool                                _run;
    Socket                              *_socket;
    Gameplay                           * _core;
    std::vector<Server::Client*>        _clients;

public:
    Server(int port, int nbPlayer);
    ~Server(void);

private:    
    /* Initialise les fd_set pour le serveur et les clients connectes */
    int                     initSelect(struct timeval &tv, fd_set *readfds, fd_set *writefds = NULL) const;
    void                    run(void);
    void                    handleSockets(void);
    bool                    checkClient(int client);
    void                    eventServer(void);
    void                    eventClients(fd_set *readfds, fd_set *writefds);
    void                    eventTerminal(void);
    void                    sendMessageAllClients(Network::cmd cmd, std::string const &msg) const;
    bool                    gameCanStart() const;
    void                    sendMapClient(Server::Client *client);
  void                    initGame();
  void                    receiveClientAction(Server::Client *client, Command::Action action);
    void                    sendCmdAck(Server::Client *client) const;
};


bool    isVerified(Server::Client &client);

#endif /* SERVER_HH */
