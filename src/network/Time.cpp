#include "Time.hh"

unsigned int Time::getMicroTimestamp(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * static_cast<unsigned int>(1000000) + tv.tv_usec;
}

unsigned int Time::getTimestamp(void)
{
    return static_cast<unsigned int>(time(NULL));
}
