//
// Created by pedro on 01/12/21.
//
#ifndef AIRLINE_SERVICE_H
#define AIRLINE_SERVICE_H

#include <string>
#include "Time.h"
#include "Schedule.h"
using namespace std;

enum Type{maintenance,cleaning};


class Service {
    const Time CLEANING_DURATION = Time(1,0);
    const Time MAINTENANCE_DURATION = Time(24,0);
private:
    Type type_service;
    Schedule schedule;
    string name_of_employee;
public:
    Time get_duration() const;
};


#endif //AIRLINE_SERVICE_H
