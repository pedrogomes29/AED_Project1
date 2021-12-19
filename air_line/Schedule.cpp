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

void Schedule::add_time(const Time&t){
    int min = get_time().get_minute()+t.get_minute();
    int hour = get_time().get_hour()+t.get_hour();
    if(min>60){
        min = min%60;
        hour+=hour/60;
    }
    if(hour>23){
        date.increment(hour/24);
        hour%=24;
    }
    time.set_hour(hour);
    time.set_minute(min);
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