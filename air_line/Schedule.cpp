//
// Created by pedro on 01/12/21.
//

#include "Schedule.h"
Schedule::Schedule(){
    time=Time();
    date = Date();
}

Schedule::Schedule(Time time, Date date) {
    this->time = time;
    this->date = date;
}

Time Schedule::get_time()const{
    return time;
}
Date Schedule::get_date()const{
    return date;
}

bool Schedule::operator<(Schedule const &schedule2){
    if(date<schedule2.get_date()){
        return true;
    }
    else if (schedule2.get_date()<date){
        return false;
    }
    else{
        if(time<schedule2.get_time()){
            return true;
        }
        else{
            return false;
        }
    }
}
istream& operator>> (istream& stream, Schedule &s){
    stream >> s.date >> s.time;
    return stream;
}

ostream& operator<< (ostream& stream, const Schedule &s){
    stream << s.date << " " << s.time;
    return stream;
}