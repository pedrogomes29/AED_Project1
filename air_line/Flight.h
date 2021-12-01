//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_FLIGHT_H
#define AIRLINE_FLIGHT_H

#include <string>
#include "Passenger.h"
#include <vector>
#include "Date.h"
#include "Schedule.h"

using namespace std;

class Flight {
private:
    unsigned capacity;
    unsigned number;
    double duration;
    Schedule date_of_departure;
    string origin;
    string destination;
    vector<Passenger> passengers;
public:
    Flight(unsigned capacity,unsigned number,double duration,const string& date_of_departure, unsigned hour,unsigned minute, string origin,
           string destination, vector<Passenger> passengers);
    bool add_passenger(Passenger p);
};



#endif //AIRLINE_FLIGHT_H