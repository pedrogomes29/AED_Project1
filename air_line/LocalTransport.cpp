//
// Created by Rui on 14/12/2021.
//

#include "LocalTransport.h"

LocalTransport::LocalTransport() {
 distance = 0;
 type = "";
 schedules = vector<Schedule>();
}

LocalTransport::LocalTransport(float distance, string type, vector<Schedule> schedules) {
    this-> distance = distance;
    this-> type = type;
    this -> schedules = schedules;
}

bool LocalTransport::operator<(LocalTransport &lt1) const {
    return this->distance < lt1.distance;
}

float LocalTransport::get_distance() const {
    return distance;
}

void LocalTransport::set_distance(float &d) {
    distance = d;
}

string LocalTransport::get_type() const {
    return type;
}

void LocalTransport::set_type(string &t) {
    type = t;
}

vector<Schedule> LocalTransport::get_schedules() const {
    return schedules;
}

void LocalTransport::set_schedules(vector<Schedule> &s) {
    schedules = s;
}

void LocalTransport::add_schedule(Schedule s) {
    this->schedules.push_back(s);
}

