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
    Airplane();
    Airplane(string _license_plate,string _type,unsigned _capacity);
    string get_license_plate() const;
    string get_type() const;
    unsigned get_capacity() const;
    bool remove_service();
    queue<Service> get_services() const;
    list<Flight> get_flights() const;
    Flight & find_flight(unsigned number);
    bool add_flight(Flight f);
    bool remove_flight(unsigned number);
    void update_flights();
    bool add_service(Service serv);
};


#endif //AIRLINE_AIRPLANE_H
