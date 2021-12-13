//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_SCHEDULE_H
#define AIRLINE_SCHEDULE_H


#include "Date.h"
#include "Time.h"
#include <istream>
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
    friend istream& operator>> (istream& stream, Schedule &s);
    friend ostream& operator<< (ostream& stream,const Schedule &s);
};


#endif //AIRLINE_SCHEDULE_H
