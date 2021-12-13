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
int Time::get_hour() const{
    return hour;
}
int Time::get_minute() const{
    return minute;
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
