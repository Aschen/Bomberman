#ifndef SERVER_HH
# define SERVER_HH

#include <vector>
#include <algorithm>
#include <sys/select.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sstream>
#include "Socket.hh"
#include "Network.hh"
#include "Gameplay.hh"
#include "Maps.hh"

class   Server
{
public:
    const static int                PORT = 4242;

/*  Nested Classe pour gérer les différents clients se connectant au serveur  */
public:
    class   Client : public Socket
    {
    private:
        bool            _verified;

    public:
        Client(Socket &socket);
        ~Client(void);

    public:
        bool            isVerified(void) const;
        void            setVerified(bool verified);
    };

private:
    Socket                              *_socket;
    bool                                _multiplayers;
    Gameplay                           * _core;
    unsigned int                        _nbPlayers;
    std::vector<Server::Client*>        _clients;
    bool                                _play;
    std::string                         _map;

public:
    Server(int port = Server::PORT);
    ~Server(void);

private:    
    /* Initialise les fd_set pour le serveur et les clients connectes */
    int                     initSelect(struct timeval &tv, fd_set *readfds, fd_set *writefds = NULL);
    void                    run(void);
    void                    handleSockets(void);
    bool                    checkClient(int client);
    bool                    eventServer(void);
    bool                    eventTerminal(void);
    bool                    eventClients(fd_set *readfds, fd_set *writefds);
    bool                    sendMessageAllClients(Network::cmd cmd, std::string const &msg);
    void                    gameCanStart();
    void                    sendMapClient(Server::Client *client);
};


bool    isVerified(Server::Client &client);

#endif /* SERVER_HH */
