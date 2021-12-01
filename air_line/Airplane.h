//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_AIRPLANE_H
#define AIRLINE_AIRPLANE_H

#include <string>
#include <queue>
#include <list>
#include <ctime>
#include "Service.h"
#include "Airplane.h"
#include "Flight.h"
using namespace std;

class Airplane {
private:
    string license_plate;
    string type;
    unsigned capacity;
    queue<Service> services;
    list<Flight> flights;
public:
    Airplane(string _license_plate,string _type,unsigned _capacity);
    bool add_flight(Flight f);
    void update_flights();
};


#endif //AIRLINE_AIRPLANE_Hs
