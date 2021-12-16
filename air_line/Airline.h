//
// Created by pedro on 05/12/21.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Airplane.h"
#include "Airport.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class Airline {
private:
    vector<Airplane> airplanes;
    vector<Airport> airports;
public:
    /*
     * Default constructor of the AirLine class
     * This Constructor is responsible for reading every single data stored in local files
     * It reads every airplane, flight, services and passengers that were created in the past and are associated and stored in this airline
     */
    Airline();
    /*
     * Destructor of the Airline class
     * This Constructor is responsible for writing every single new creation and possible modification to the text files.
     * containing all the assets of the airline
     * It writes every airplane, flight, services and passengers that were created while the program ran and in its respective text file.
     * Every airplane and every flight have its own text file.
     * The passengers are stored in the flight file corresponding to the flight where they checked in
     * The services are stored in the airplane file corresponding to the airplane where we want to clean/repair
     */
    ~Airline();
    /**
     * Simple text based interface to interact with the user and read their desired input
     */
    void interface();
    /*
     * Function that trys to add an airplane to
     */
    bool add_airplane();
    void check_db();
    void update_airplane(Airplane &airplane);
    void update_flight(Flight &flight);
    void setup();
    Airplane* find_airplane(const string& license_plate);
    bool add_flight(Airplane & airplane);
    bool add_airport(const Airport &airport);
    void check_new_transports(const Airport & airport);
    void see_information_transport(const LocalTransport &l);
    Airport * find_airport(const string &name);
    void print_closest_transports(const Airport &airport);
    void print_planes(char c);
    void print_airports(string country);
    void print_soonest_flights(int n);
};

#endif //AIRLINE_AIRLINE_H
