//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_TIME_H
#define AIRLINE_TIME_H


class Time {
private:
    int hour;
    int minute;
public:
    Time();
    Time(int hour,int minute);
    int get_hour() const;
    int get_minute() const;
    bool operator<(Time const &time2);
};


#endif //AIRLINE_TIME_H
