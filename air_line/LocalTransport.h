//
// Created by Rui on 14/12/2021.
//

#ifndef AIRLINE_LOCALTRANSPORT_H
#define AIRLINE_LOCALTRANSPORT_H

#include "Time.h"
#include <string>
#include <vector>

using namespace std;

class LocalTransport {
private:
    string name;
    float distance;
    string type;
    vector<Time> schedules;
public:
    LocalTransport();
    LocalTransport(string name,float distance,string type,vector<Time> schedules);
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
