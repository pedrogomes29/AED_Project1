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
     * It writes every airplane, flight, services and passengers
     * that were created while the program ran and in its respective text file.
     * Every airplane and every flight have its own text file.
     * The passengers are stored in the flight file corresponding to the flight where they checked in
     * The services are stored in the airplane file corresponding to the airplane where we want to clean/repair
     */
    ~Airline();
    /**
     * Simple text based interface to interact with the user and read their desired input
     */
    void interface();
    /**
     * Function that trys to add an object of the Airplane Class to the ordered vector airplanes
     * @return returns a boolean value representing whether it was possible to add an airplane to the
     * correct position of the ordered vector airplanes or not
     */
    bool add_airplane();
    /**
     * Method that displays various listings of assets of the airline to the user.
     * Gives the user some power in the way he wants to see those listings.
     */
    void check_db();
    /**
     * Method that acts as an interface to get input from the user regarding what changes they want to make in a certain airplane
     * Such as adding and removing flights/services.
     * Also displays the order in which every passenger luggage boards the airplane.
     * @param airplane object of class Airplane passed by reference which represents the plane we want to make changes on.
     */
    void update_airplane(Airplane &airplane);
    /**
     * Method that acts as an interface to get input from the user regarding what changes they want to make in a certain airplane.
     * Such as adding passengers or changing the schedule of a flight.
     * @param flight object of class FLight passed by reference which represents the flight we want to make changes on.
     */
    void update_flight(Flight &flight);
    /**
     * Method that initializes every operational Airport of this Airline.
     * And also populates the bst transports of every airport with its nearest transports.
     */
    void setup();
    /**
     * Simple binary search method which finds a given airplane in the ordered vector airplanes.
     * @param license_plate string passed by reference which represents the license plate of the airplane we want to find
     * @return returns a pointer to an object of the class Airplane which points to the airplane we wanted to find
     * or to a null pointer in case it wasn't found
     */
    Airplane* find_airplane(const string& license_plate);
    /**
     * Method that adds a flight to a certain airplane with details given by the user
     * @param airplane object of class Airplane passed by reference in which the flight will be added
     * @return boolean value representing whether it was possible to add the flight given by the user.
     */
    bool add_flight(Airplane & airplane);
    /**
     * Method that adds an object of class Airport to the ordered vector airports.
     * @param airport object of class Airport passed by reference which we want to add on the ordered vector
     * @return boolean value representing whether it was possible to add the airport given by the user
     * in the correct place of the vector
     */
    bool add_airport(const Airport &airport);
    /**
     * Method that displays listings of local transports of a given airport
     * The user has power in the number of nearest transports they want to see
     * And also what type of transport they wish get info about.
     * @param airport object of class Airport passed by reference which we want to obtain info about its nearest transports.
     */
    void check_new_transports(const Airport & airport);
    /**
     * Displays information about a nearest local transport of an airport.
     * We provide the user a list of the next schedules of a certain transport
     * @param l object of class Local Transport passed by reference which we want to obtain info about its schedules.
     */
    void see_information_transport(const LocalTransport &l);
    /**
     * Simple binary search method which finds a given airplane in the ordered vector airplanes.
     *
     * @param name
     * @return
     */
    Airport * find_airport(const string &name);
    /**
     * Method that prints to the console the listings of local transports of a given airport
     * @param airport object of class Airport passed by reference which we want to obtain info about its nearest transports.
     */
    void print_closest_transports(const Airport &airport);
    /**
     * Method that prints the listing of airplanes according to the sorting rule of the user
     * @param c character that was chosen by the user can be either A,B or C
     * and is responsible of selecting the sorting rule the user chose
     */
    void print_planes(char c);
    /**
     * Method that prints to the console the listing of airports either of a given country or all the airports by alphabetic order.
     * @param country string representing the country that we want to display the airports of. Can also
     * be 'x', in that case all functional airports will be displayed.
     */
    void print_airports(string country);
    /**
     * Method that prints to the console the listing of the next n soonest flights.
     * @param n integer representing the number of soonest flights the user wants to see.
     */
    void print_soonest_flights(int n);
};

#endif //AIRLINE_AIRLINE_H
