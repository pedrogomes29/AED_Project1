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
    Time get_time()const;
    Date get_date()const;
    bool operator<(Schedule const &schedule2);
};


#endif //AIRLINE_SCHEDULE_H
