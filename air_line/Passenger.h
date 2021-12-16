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
    /**
     * Constructor of the Passenger class
     * @param name name of the passenger
     * @param luggage boolean representing if the passenger checked in with luggage
     */
    Passenger(const string &name,bool luggage);
    /**
     * getter for the luggage attribute
     * @return returns a boolean value indicating whether the passenger checked in with luggage
     */
    bool has_luggage() const;
    /**
     * getter for the name of the passenger
     * @return returns a string representing the passenger name
     */
    string get_name() const;
};


#endif //AIRLINE_PASSENGER_H
