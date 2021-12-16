//
// Created by pedro on 05/12/21.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Airplane.h"
#include "Airport.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class Airline {
private:
    list<Airplane> airplanes;
    vector<Airport> airports;
public:
    Airline();
    ~Airline();
    void interface();
    void add_airplane();
    void check_db();
    void update_airplane(Airplane &airplane);
    void update_flight(Flight &flight);
    void setup();
    void add_passenger(Flight &flight);
    Airplane* find_airplane(const string& license_plate);
    bool add_flight(Airplane & airplane);
    bool add_airport(const Airport &airport);
    void check_new_transports(const Airport & airport);
    bool find_airport(const string &name,Airport * &airportptr);
    void print_planes(char c);
    void print_airports(string country);
    void print_soonest_flights(int n);
};

#endif //AIRLINE_AIRLINE_H
