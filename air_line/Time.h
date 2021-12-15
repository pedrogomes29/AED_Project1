//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_TIME_H
#define AIRLINE_TIME_H
#include <istream>
using namespace std;
class Time {
private:
    int hour;
    int minute;
public:
    Time();
    Time(int hour,int minute);
    void set_hour(int hour);
    void set_minute (int minute);
    int get_hour() const;
    int get_minute() const;
    bool operator<(Time const &time2) const;
    friend istream &operator>>(istream& stream,  Time& t);
    friend ostream &operator<< (ostream& stream, const Time& t);
    Time operator+(const Time &t2) const;
};


#endif //AIRLINE_TIME_H
