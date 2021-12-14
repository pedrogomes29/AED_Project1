//
// Created by Rui on 14/12/2021.
//

#include "LocalTransport.h"

LocalTransport::LocalTransport() {
    name = "";
    distance = 0;
    type = "";
    schedules = vector<Time>();
}

LocalTransport::LocalTransport(string name, float distance, string type, vector<Time> schedules) {
    this-> name = name;
    this-> distance = distance;
    this-> type = type;
    this -> schedules = schedules;
}

bool LocalTransport::operator<(const LocalTransport &lt1) const{
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

vector<Time> LocalTransport::get_schedules() const {
    return schedules;
}

void LocalTransport::set_schedules(vector<Time> &s) {
    schedules = s;
}

void LocalTransport::add_schedule(Time s) {
    for(auto iter= schedules.begin();iter!=schedules.end();iter++){
        if(s<*iter)
            schedules.insert(iter,s);
    }
}

vector<Time> LocalTransport::next_schedules(int n, Time t) {
    if(n>schedules.size()) return schedules;
    vector<Time> result;
    auto iter = schedules.begin();
    bool next_day = false;
    while(n){
        if(t<*iter or next_day) result.push_back(*iter);
        n--;
        iter++;
        if (iter==schedules.end()){
            iter=schedules.begin();
            next_day = true;
        }
    }
    return result;
}

