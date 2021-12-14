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
};



#endif //AIRLINE_LOCALTRANSPORT_H
