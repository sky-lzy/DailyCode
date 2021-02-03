#ifndef TIME_H
#define TIME_H

class time
{
private:
    int sec;
    int min;
    int hour;

public:
    time();
    time(int, int, int);
    ~time();
    time operator++();
    void ShowTime();
};

#endif