#include "Debug.hh"

Debug::Debug(std::string filename) : _fd(NULL), _display(false)
{
    std::string     msg("\n-----------------------------\n-----------------------------\n--    Start log session    --\n-----------------------------\n-----------------------------\n");

    _fd = fopen(filename.c_str(), "a");
    if (_fd == NULL)
    {
        std::cerr << "Can't open log file " << filename << std::endl;
    }
    if (fwrite(msg.c_str(), sizeof(char), msg.length(), _fd) != msg.length())
    {
        std::cerr << "Can't write in log file" << std::endl;
    }
}

Debug::~Debug(void)
{
    if (_fd != NULL)
    {
        fclose(_fd);
    }
}

void Debug::setDisplay(bool display)
{
    _display = display;
}

void Debug::addDebug(std::string msg)
{
    std::string         debug;

    debug.append(this->getDate());
    debug.append(" - ");
    debug.append(msg);
    debug.append("\n");
    if (fwrite(debug.c_str(), sizeof(char), debug.length(), _fd) != debug.length())
    {
        std::cerr << "Can't write in log file" << std::endl;
    }
    if (_display)
    {
        std::cerr << msg << std::endl;
    }
}

std::string Debug::getDate(void)
{
    time_t          ts;
    std::string     date;

    if (time(&ts) < 0)
    {
        std::cerr << "Can't get date" << std::endl;
        return std::string("NaN");
    }
    date.append(ctime(&ts));
    date[date.length() - 1] = '\0';
    return date;
}
