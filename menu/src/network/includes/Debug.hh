#ifndef DEBUG_HH
#define DEBUG_HH

#include <string>
#include <iostream>
#include <stdio.h>

class Debug
{
private:
    FILE        *_fd;
    bool        _display;

public:
    Debug(std::string filename);
    ~Debug(void);

public:
    void            setDisplay(bool display);
    void            setSource(std::string source);
    void            addDebug(std::string msg);

private:
    std::string     getDate(void);
};

#endif // DEBUG_HH
