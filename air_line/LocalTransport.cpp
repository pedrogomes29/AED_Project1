//
// Created by Rui on 14/12/2021.
//

#include "LocalTransport.h"

LocalTransport::LocalTransport() {
 distance = 0;
 type = "";
 schedules = list<Schedule>();
}

LocalTransport::LocalTransport(float distance, string type, list<Schedule> schedules) {
    this-> distance = distance;
    this-> type = type;
    this -> schedules = schedules;
}

