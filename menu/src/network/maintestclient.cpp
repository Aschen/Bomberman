#include "Server.hh"
#include "Client.hh"

int     main(int ac, char **av)
{

    std::string address("127.0.0.1");
    int port = Server::PORT;

    if (ac > 1)
        address = av[1];


    std::cout << "adress : " <<  address << std::endl;
    std::cout << "port : " <<  port << std::endl;



    Client client(address, port);


    return 0;
}
