//
// Created by pedro on 05/12/21.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Airplane.h"
#include "Airport.h"
#include <string>
#include <list>

using namespace std;

class Airline {
private:
    list<Airplane> airplanes;
    list<Airport> airports;
public:
    Airline();
    ~Airline();
    void interface();
    void add_airplane();
    void check_airplanes();
    void update_airplane(Airplane &airplane);
    void update_flight(Flight &flight);
    void add_passenger(Flight &flight);
    Airplane* find_airplane(const string& license_plate);
    bool add_flight(Airplane & airplane);
    bool add_airport(const string &name);
    bool find_airport(const string &name,Airport * airportptr);
};

#endif //AIRLINE_AIRLINE_H
