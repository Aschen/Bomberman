#ifndef TIME_HH
#define TIME_HH

#include <string>
#include <time.h>
#include <sys/time.h>

class Time
{
public:
    static unsigned int       getMicroTimestamp(void);
    static unsigned int       getTimestamp(void);
};

#endif // TIME_HH
