//
// Created by pedro on 01/12/21.
//

#include "Airplane.h"

Airplane::Airplane(string _license_plate,string _type,unsigned _capacity){
    license_plate = _license_plate;
    type=_type;
    capacity=_capacity;
}

bool Airplane::add_flight(Flight f){
    auto iter = flights.begin();
    auto previous = flights.begin();
    while(iter->get_schedule()<f.get_schedule() and iter!=flights.end()){
        previous = iter;
        iter++;
    }
    if(previous->get_destination()==f.get_origin() and 
}
