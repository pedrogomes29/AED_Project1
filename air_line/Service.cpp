//
// Created by pedro on 01/12/21.
//

#include "Service.h"

Time CLEANING_DURATION = Time(1,0);
Time MAINTENANCE_DURATION = Time(24,0);

Service::Service(Type type,const string &date,int hour, int minute, const string &name){
    this->type_service=type;
    if(type==maintenance)
        this->duration = MAINTENANCE_DURATION;
    else
        this->duration = CLEANING_DURATION;
    this->schedule = Schedule(Time(hour,minute),Date(date));
    this->name_of_employee=name;
}

