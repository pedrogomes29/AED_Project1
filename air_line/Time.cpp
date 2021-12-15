//
// Created by pedro on 01/12/21.
//

#include "Time.h"

Time::Time(){
    hour = 0;
    minute = 0;
}
Time::Time(int hour,int minute) {
    this->hour = hour;
    this->minute = minute;
}
Time Time::operator+(const Time &t2) const{
    int new_minute = this->get_minute()+t2.get_minute();
    int new_hour = this->get_hour()+t2.get_hour();
    if(new_minute>=60) {
        new_minute -= 60;
        new_hour++;
    }
    if(new_hour>=24)
        new_hour-=24;
    return Time(new_hour,new_minute);
}

bool Time::operator< (Time const &time2) const{
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
int Time::get_hour() const{
    return hour;
}
int Time::get_minute() const{
    return minute;
}

void Time::set_hour(int hour){
    this->hour=hour;
}
void Time::set_minute (int minute){
    this->minute=minute;
}
istream &operator>>(istream& stream,Time& t){
    char aux_char;
    stream>>t.hour >> aux_char >> t.minute;
    return stream;
}

ostream & operator<<(ostream& stream,const Time&t){
    stream << t.hour << ":" << t.minute;
    return stream;
}

