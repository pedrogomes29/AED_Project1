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
    /**
     *
     * @param type type of service either cleaning or maintenance as declared on the enum
     * @param schedule date and time of when the service is scheduled
     * @param name_of_employee name of the person in charge of the given service
     */
    Service(Type type,const Schedule & schedule,const string&name_of_employee);
    /**
     *
     * @return getter for the type of service
     */
    Type get_type() const;
    /**
     *
     * @return getter for the duration of the service
     */
    Time get_duration() const;
    /**
     *
     * @return getter for the date and time of when the service was scheduled
     */
    Schedule get_schedule() const;
    /**
     *
     * @return getter for the name of employee in charge
     */
    string get_name() const;
};




#endif //AIRLINE_SERVICE_H
