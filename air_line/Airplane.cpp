//
// Created by pedro on 01/12/21.
//

#include "Airplane.h"

Airplane::Airplane(string _license_plate,string _type,unsigned _capacity){
    license_plate = _license_plate;
    type=_type;
    capacity=_capacity;
}

Schedule result(Schedule s,Time t){
    int min = s.get_time().get_minute()+t.get_minute();
    int hour = s.get_time().get_hour()+t.get_hour();
    Date d = s.get_date();
    if(min>60){
        min = min%60;
        hour+=hour/60;
    }
    if(hour>23){
        d.increment(hour/24);
        hour%=24;
    }
    return Schedule(Time(hour,min),d);
}

bool Airplane::add_flight(Flight f){
    if(flights.empty()){
        flights.insert(flights.begin(),f);
        return true;
    }
    else {
        auto iter = flights.begin();
        auto previous = flights.begin();
        while (iter->get_schedule() < f.get_schedule() and iter != flights.end()) {
            previous = iter;
            iter++;
        }
        Schedule arrival = result(previous->get_schedule(), previous->get_duration());
        if (previous->get_destination() == f.get_origin() and arrival < f.get_schedule()) {
            flights.insert(iter, f);
            return true;
        }
        return false;
    }
}

void Airplane::update_flights(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    Schedule time_now(Time(now->tm_hour,now->tm_min),Date(now->tm_mday,now->tm_mon+1,now->tm_year+1900));
    auto iter = flights.begin();
    while(iter->get_schedule()<time_now and iter!=flights.end()){
        auto aux = iter;
        iter++;
        flights.erase(aux);
    }
}