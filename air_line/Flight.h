//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_FLIGHT_H
#define AIRLINE_FLIGHT_H

#include <string>
#include <list>
#include "Passenger.h"
#include "Date.h"
#include "Schedule.h"

using namespace std;

class Flight {
private:
    unsigned capacity;
    unsigned number;
    Time duration;
    Schedule schedule;
    string origin;
    string destination;
    list<Passenger> passengers;
public:
    Flight();
    Flight(unsigned capacity,unsigned number,Time duration,const string& date_of_departure, unsigned hour,unsigned minute, string origin,
           string destination, list<Passenger> passengers);
    Flight(unsigned capacity,unsigned number,Time duration,Schedule schedule,string origin,string destination);
    Schedule get_schedule()const;
    void set_schedule(const Schedule & s1);
    bool add_passenger(Passenger p);
    unsigned get_number() const;
    Time get_duration() const;
    unsigned get_capacity () const;
    string get_origin() const;
    string get_destination() const;
    list<Passenger> get_passengers() const;
};
;


#endif //AIRLINE_FLIGHT_H