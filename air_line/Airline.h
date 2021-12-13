//
// Created by pedro on 05/12/21.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Airplane.h"
#include <string>
#include <list>

using namespace std;

class Airline {
private:
    list<Airplane> airplanes;
public:
    Airline();
    ~Airline();
    void interface();
    void add_airplane();
    void check_airplanes(const Airplane &airplane);
    void update_airplane(Airplane &airplane);
    void update_flight(Flight &flight);
    void add_passenger(Flight &flight);
    Airplane& find_airplane(const string &license_plate);
};


#endif //AIRLINE_AIRLINE_H
