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

Time Schedule::get_time(){
    return time;
}
Date Schedule::get_date(){
    return date;
}