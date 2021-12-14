//
// Created by Rui on 14/12/2021.
//

#ifndef AIRLINE_LOCALTRANSPORT_H
#define AIRLINE_LOCALTRANSPORT_H

#include "Time.h"
#include <vector>
#include <string>
#include <vector>

using namespace std;

class LocalTransport {
private:
    float distance;
    string type;
    vector<Time> times;
public:
    LocalTransport();
    LocalTransport(float distance,string type,vector<Time> times);
    float get_distance() const;
    void set_distance(float &d);
    string get_type() const;
    void set_type(string &t);
    vector<Time> get_schedules() const;
    void set_schedules(vector<Time> &s);
    void add_schedule(Time s);
    bool operator<(LocalTransport &lt1) const;
};



#endif //AIRLINE_LOCALTRANSPORT_H
