//
// Created by rui on 01/12/21.
//

#include "Flight.h"

Flight::Flight(unsigned int capacity, unsigned int number, double duration, const string& date_of_departure, string origin,
               string destination, vector<Passenger> passengers) {
this->capacity = capacity;
this->number = number;
this->duration = duration;
this->date_of_departure = Date(date_of_departure);
this-> origin = origin;
this->destination = destination;
this-> passengers = passengers;
}

bool Flight::add_passenger(Passenger p) {

}
