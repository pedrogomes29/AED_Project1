//
// Created by pedro on 01/12/21.
//

#include "Time.h"

Time::Time(){
    hour = 0;
    minute = 0;
}
Time::Time(unsigned int hour, unsigned int time) {
    this->hour = hour;
    this->minute = minute;
}


unsigned Time::get_hour() const{
    return hour;
}
unsigned Time::get_minute() const{
    return minute;
}
