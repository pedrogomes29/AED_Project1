//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_PASSENGER_H
#define AIRLINE_PASSENGER_H

#include <string>

using namespace std;

class Passenger {
private:
    string name;
    bool luggage;
public:
    Passenger(const string &name,bool luggage);
    bool has_luggage() const;
    string get_name() const;
};


#endif //AIRLINE_PASSENGER_H
