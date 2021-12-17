//
// Created by pedro on 01/12/21.
//

#ifndef AIRLINE_AIRPLANE_H
#define AIRLINE_AIRPLANE_H

#include <vector>
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
    vector<Flight> flights;
public:
    /**
     * Default constructor of the Airplane class
     * Default plane consists of a plane with license plate "", type "" and capacity 0
     */
    Airplane();
    /**
     * Constructor of the Airplane Class
     * @param _license_plate string representing the license plate of the airplane
     * @param _type string representing the type of the airplane
     * @param _capacity unsigned int representing the capacity  of the airplane
     */
    Airplane(string _license_plate,string _type,unsigned _capacity);
    /**
     * getter for the license plate attribute
     * @return returns string representing the license plate of the airplane
     */
    string get_license_plate() const;
    /**
     * getter for the type attribute
     * @return returns string representing the type of the airplane
     */
    string get_type() const;
    /**
     * getter for the capacity attribute
     * @return returns unsigned int representing the capacity  of the airplane
     */
    unsigned get_capacity() const;
    /**
     * method that trys to remove the next service in the queue of services of the airplane
     * @return returns a boolean value indicating if the removal was possible, that is if the queue of services was not empty
     */
    bool remove_service();
    /**
     * getter for the services attribute
     * @return returns a queue of objects of the class service representing the services attribute
     */
    queue<Service> get_services() const;
    /**
     * getter for the flights attribute
     * @return returns an ordered vector of objects (ordered by schedule) of the class flight representing the flights attribute
     */
    vector<Flight> get_flights() const;
    /**
     * Method that trys ot find a flight of flight number n assigned to this airplane
     * @param number unsigned int representing the number of the flight we want to find
     * @return returns a pointer to a flight if that flight existed in the vector flight, else returns a null pointer
     */
    Flight* find_flight(unsigned number);

    void start_flight();

    bool cancel_flights(const vector<unsigned>& numbers);


    void add_flight(const Flight &f);

    bool check_if_in_order_adding(const vector<Flight> &flights) const;

    bool check_if_in_order_removing(const vector<Flight> &flights);
    /**
     * method that adds a flight in its correct position in the ordered vector flights.
     * @param flights vector of objects of class Flight passed by reference that we want to add to the flights vector.
     * @return returns if it was possible to add the flights or not.
     */
    bool add_flights(vector<Flight> flights);
    /**
     * method that trys to add a service to the back of the queue of services in this plane
     * @param serv object of class Service that we want to add in the queue
     * @return returns a boolean value indicating whether the insertion was possible because
     * we cannot add a service at the same time a flight is taking place
     */
    bool add_service(const Service& serv);
};

#endif //AIRLINE_AIRPLANE_H
