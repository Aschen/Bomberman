#include <cstdlib>
#include <GameEngine.hh>
#include <Menu.hh>
#include <vector>
#include <Graph.hh>
#include <Gameplay.hh>
#include <Maps.hh>
#include <Cursor.hh>

void    displayUsage(std::string progName)
{
    std::cout << "Usage : " << std::endl;
    std::cout << "\t" << progName << " server [players] [port]" << std::endl;
    std::cout << "\t" << progName << " client [ip] [port]" << std::endl;
    std::cout << "\t Default port is 1337." << std::endl;
}

int main(int ac, char **av)
{
    int port = Server::PORT;    

    if (ac < 3)
    {
        displayUsage(av[0]);
        return 1;
    }
    if (ac == 4)
    {
        std::stringstream   ss(av[3]);
        ss >> port;
    }
    try
    {
        if (std::string(av[1]) == "client")
            Client client(av[2], port);
        else if (std::string(av[1]) == "server")
        {
            int                 nbPlayers;
            std::stringstream   ss(av[2]);

            ss >> nbPlayers;
            Server server(port, nbPlayers);
        }
        else
            displayUsage(av[0]);
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
