//
// Created by rui on 01/12/21.
//

#include "Passenger.h"


Passenger::Passenger(const string &name,bool luggage){
    this->name = name;
    this->luggage = luggage;
}


bool Passenger::has_luggage() const{
    return luggage;
}
string Passenger::get_name() const{
    return name;
}