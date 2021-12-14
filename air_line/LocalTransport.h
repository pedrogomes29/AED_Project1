//
// Created by Rui on 14/12/2021.
//

#ifndef AIRLINE_LOCALTRANSPORT_H
#define AIRLINE_LOCALTRANSPORT_H

#include "Schedule.h"
#include <list>
#include <string>
#include <vector>

using namespace std;

class LocalTransport {
private:
    float distance;
    string type;
    vector<Schedule> schedules;
public:
    LocalTransport();
    LocalTransport(float distance,string type,vector<Schedule> schedules);
    float get_distance() const;
    void set_distance(float &d);
    string get_type() const;
    void set_type(string &t);
    vector<Schedule> get_schedules() const;
    void set_schedules(vector<Schedule> &s);
    void add_schedule(Schedule s);
    bool operator<(LocalTransport &lt1) const;
};



#endif //AIRLINE_LOCALTRANSPORT_H
