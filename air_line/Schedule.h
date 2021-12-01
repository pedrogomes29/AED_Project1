//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_SCHEDULE_H
#define AIRLINE_SCHEDULE_H


#include "Date.h"
#include "Time.h"
class Schedule {
private:
    Time time;
    Date date;
public:
    Schedule();
    Schedule(Time time,Date date);
    Time get_time();
    Date get_date();
};


#endif //AIRLINE_SCHEDULE_H
