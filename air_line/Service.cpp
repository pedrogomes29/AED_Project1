//
// Created by pedro on 01/12/21.
//

#include "Service.h"


Service::Service(Type type,const string &date,int hour, int minute, const string &name){
    this->type_service=type;
    this->schedule = Schedule(Time(hour,minute),Date(date));
    this->name_of_employee=name;
}