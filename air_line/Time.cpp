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


bool Time::operator< (Time const &time2){
    if(hour<time2.get_hour()){
        return true;
    }
    else if (time2.get_hour()<hour){
        return false;
    }
    else{
        if(minute<time2.get_minute()){
            return true;
        }
        else{
            return false;
        }
    }
}
unsigned Time::get_hour() const{
    return hour;
}
unsigned Time::get_minute() const{
    return minute;
}