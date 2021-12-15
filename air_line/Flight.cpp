//
// Created by rui on 01/12/21.
//

#include "Flight.h"

Flight::Flight() {
    this->capacity = 0;
    this->number = 0;
    this->duration = Time(0,0);
    this->schedule = Schedule(Time(0,0),Date(0,0,0));
    this-> origin = "";
    this->destination = "destination";
}

Flight::Flight(unsigned capacity,unsigned number,Time duration,const string& date_of_departure, unsigned hour,unsigned minute, string origin,
               string destination, vector<Passenger> passengers){
this->capacity = capacity;
this->number = number;
this->duration = duration;
this->schedule = Schedule(Time(hour,minute),Date(date_of_departure));
this-> origin = origin;
this->destination = destination;
this-> passengers = passengers;
}

Flight::Flight(unsigned capacity,unsigned number,Time duration,Schedule schedule,string origin,string destination){
    this->capacity = capacity;
    this->number = number;
    this->duration = duration;
    this->schedule = schedule;
    this-> origin = origin;
    this->destination = destination;
}

void Flight::set_schedule(const Schedule & s1){
   schedule=s1;
}

Schedule Flight::get_schedule() const {
    return schedule;
}
bool Flight::add_passenger(Passenger p) {
    if(passengers.size()<capacity){
        passengers.push_back(p);
        return true;
    }
    return false;
}


unsigned Flight::get_number() const {
    return number;
}

Time Flight::get_duration() const {
    return duration;
}

string Flight::get_origin() const{
    return origin;
}

string Flight::get_destination() const {
    return destination;
}

vector<Passenger> Flight::get_passengers() const {
    return passengers;
}

unsigned Flight::get_capacity () const{
    return capacity;
}


