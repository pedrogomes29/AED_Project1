//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_TIME_H
#define AIRLINE_TIME_H


class Time {
private:
    unsigned hour;
    unsigned minute;
public:
    Time();
    Time(unsigned hour,unsigned time);
    unsigned get_hour();
    unsigned get_minute();
};


#endif //AIRLINE_TIME_H
