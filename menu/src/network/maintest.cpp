#include "Server.hh"

int     main(int ac, char **av)
{
     if (ac == 2)
        Server      server(atoi(av[1]));
    else
        Server      server2;
    return 0;
}
