//
// Created by pedro on 05/12/21.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Airplane.h"

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
    void check_airplanes();
    void update_airplane();
    void update_flight();
    void add_passenger();
};


#endif //AIRLINE_AIRLINE_H
