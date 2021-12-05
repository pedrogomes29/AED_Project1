//
// Created by pedro on 01/12/21.
//
#ifndef AIRLINE_SERVICE_H
#define AIRLINE_SERVICE_H

#include <string>
#include "Schedule.h"
#include "Time.h"
#include "Schedule.h"
using namespace std;

enum Type{maintenance,cleaning};


class Service {
private:
    Type type_service;
    Time duration;
    Schedule schedule;
    string name_of_employee;
public:
    Service(Type type,const string &date,int hour, int minute,const string &name);
};




#endif //AIRLINE_SERVICE_H
