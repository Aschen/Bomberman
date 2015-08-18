#include "Network.hh"

std::string Network::cmdToString(Network::cmd cmd)
{
    std::string       str = "0";

    str[0]  = static_cast<char>(cmd + '0');
    return str;
}


Network::cmd Network::stringToCmd(std::string cmd)
{
    Network::cmd      tmp;

    tmp = static_cast<Network::cmd>(cmd[0] - '0');
    return tmp;
}
