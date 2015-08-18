#include "Client.hh"

Client::Client(std::string address, int port)
    : _socket(new Socket(address, port)), _play(false), _canAskMap(true), _canSendCmd(true)
{
    /* Initialisation de la GDL */
    _engine.initialize();
    /* Preparation des objets */
    _engine.allocObjects();

    /* Lancement de la socket */
    if (_socket->start())
    {
        std::cout << _socket->getState() << std::endl;
        run();
    }
    else
        throw std::runtime_error(_socket->getError());
}


Client::~Client(void)
{
    delete _socket;
}


void Client::run(void)
{
    bool    run = true;

    while (run)
    {
        handleSockets();
        if (run && _play)
        {
            askMap();
            run = getPlayerEvent();
        }
        usleep(400);
    }
    std::cout << "End game." << std::endl;
}


void Client::handleSockets(void)
{
    fd_set                    readfds;
    fd_set                    writefds;
    int                       fd_max;
    struct timeval            tv;
    Message                   msg;

    fd_max = initSelect(tv, &readfds, &writefds);
    if (select(fd_max, &readfds, &writefds, NULL, &tv) == -1)
    {
        throw std::runtime_error(std::string("Select Error : ") + strerror(errno));
    }
    if (FD_ISSET(_socket->get(), &writefds))
    {
        _socket->sendMsg();
    }
    if (FD_ISSET(_socket->get(), &readfds))
    {
        if (_socket->receiveMsg() == 0)
        {
            throw std::runtime_error(std::string("Lost connection to the server."));
        }
        else
        {
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
                    startGame();
                    break;
                case Network::END:
                    stopGame();
                    break;
                case Network::ACK:
                    updateCmd();
                    break;
                default:
                    std::cout << "Default switch" << std::endl;
                    break;
                }
            }
        }
    }
}

int Client::initSelect(timeval &tv, fd_set *readfds, fd_set *writefds) const
{
    int     fd_max = _socket->get();

    /* Timeout 4 secondes */
    tv.tv_sec = 0;
    tv.tv_usec = 400;

    /* On prepare les champs de bits pour select */
    FD_ZERO(readfds);
    FD_SET(_socket->get(), readfds);
    if (writefds != NULL)
    {
        FD_ZERO(writefds);
        FD_SET(_socket->get(), writefds);
    }
    return fd_max + 1;
}


void Client::askMap()
{
    if (_canAskMap)
    {
        _socket->addMessage(Message(Network::cmdToString(Network::MAP), "MAP"));
        _canAskMap = false;
    }
}



bool Client::getPlayerEvent(void)
{
    int ret = STAY;

    if (_canSendCmd)
    {
        ret = _engine.getKey(_canSendCmd);
    }
    if (ret != STAY)
    {
        switch (ret)
        {
        case ESC:
            _socket->addMessage(Message(Network::cmdToString(Network::END), "END"));
            return false;
            break;
        case UP:
//            std::cout << "Send UP" << std::endl;
            _socket->addMessage(Message(Network::cmdToString(Network::UP), "UP"));
            break;
        case DOWN:
//            std::cout << "Send DOWN" << std::endl;
            _socket->addMessage(Message(Network::cmdToString(Network::DOWN), "DOWN"));
            break;
        case LEFT:
//            std::cout << "Send LEFT" << std::endl;
            _socket->addMessage(Message(Network::cmdToString(Network::LEFT), "LEFT"));
            break;
        case RIGHT:
//            std::cout << "Send RIGHT" << std::endl;
            _socket->addMessage(Message(Network::cmdToString(Network::RIGHT), "RIGHT"));
            break;
        case SPACE:
            _socket->addMessage(Message(Network::cmdToString(Network::DBOMB), "DBOMB"));
            break;
        default:
            break;
        }
        _canSendCmd = false;
    }
    return true;
}


void Client::updateMap(Message &msg)
{
//    unsigned int size;

//    size = sqrt(msg.second.size());
//    std::cout << "----------------------------" << std::endl;
//    for (unsigned int i = 0; i < size; ++i) {
//        std::cout << "|" << msg.second.substr(i * size, size) << "|" <<std::endl;
//    }
//    std::cout << "----------------------------" << std::endl;

    std::vector<int> orientations;
    
    int i(0), nbpl(0), n(0);

    for (i = 0; i < msg.second.size(); i++)
    {
        if (msg.second[i] == PLAYER)
            nbpl++;
    }
    for (i = msg.second.size(), n = 0; n < nbpl; n++)
    {
        orientations.push_back(static_cast<int>(msg.second[i - nbpl + n]) - 48);
    }
    _engine.receiveMap(msg.second, orientations);
    _engine.update();
    _engine.draw();
    _canAskMap = true;
}


void Client::sendSynchro(void)
{
    _socket->addMessage(Message(Network::cmdToString(Network::ACK), "ACK"));
    std::cout << "Send verification msg..." << std::endl;
}


void Client::startGame()
{
    std::cout << "All players are connected. The game can start now !" << std::endl;
    _play = true;
}


void Client::stopGame(void)
{
    _play = false;
}


void Client::updateCmd(void)
{
    _canSendCmd = true;
}
