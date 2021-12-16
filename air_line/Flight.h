//
// Created by rui on 01/12/21.
//

#ifndef AIRLINE_FLIGHT_H
#define AIRLINE_FLIGHT_H

#include <string>
#include <list>
#include "Passenger.h"
#include "Date.h"
#include "Schedule.h"

using namespace std;

class Flight {
private:
    unsigned capacity;
    unsigned number;
    Time duration;
    Schedule schedule;
    string origin;
    string destination;
    list<Passenger> passengers;
public:
    /**
     * Default constructor of Flight class
     * Represents a flight of capacity 0 with the number 0
     * with the default schedule and duration = 0h:0m
     * with an "" origin and "" destination
     * and an empty list of passengers
     */
    Flight();
    /**
     * integer representing the capacity of the flight which is equal to the capacity of it's airplane
     * @param capacity integer representing the capacity of the flight which is equal to the capacity of it's airplane
     * @param number integer representing the number/id of the flight
     * @param duration object of Time Class representing the duration in hour:minutes of the class
     * @param date_of_departure string containing a date in the format dd/mm/yy
     * @param hour unsigned integer representing the hour of the flight
     * @param minute unsigned integer representing the minutes of the hour of the flight
     * @param origin string representing the airport where the flight starts
     * @param destination string representing the airport where the flight ends
     * @param passengers list of passengers containing passengers that will checked in this flight
     */
    Flight(unsigned capacity,unsigned number,Time duration,const string& date_of_departure, unsigned hour,unsigned minute, string origin,
           string destination, list<Passenger> passengers);
    /**
     * The other constructor and the most used of this class
     * @param capacity integer representing the capacity of the flight which is equal to the capacity of it's airplane
     * @param number integer representing the number/id of the flight
     * @param duration object of Time Class representing the duration in hour:minutes of the flight
     * @param schedule object of Schedule Class representing the date and hour of when the flight will take place
     * @param origin string representing the airport where the flight starts
     * @param destination string representing the airport where the flight ends
     */
    Flight(unsigned capacity,unsigned number,Time duration,Schedule schedule,string origin,string destination);
    /**
     * getter for the the date and hour of when the flight will take place
     * @return returns object of Schedule Class representing the date and hour of when the flight will take place
     */
    Schedule get_schedule()const;
    /**
     * setter for the the date and hour of when the flight will take place
     * @param s1 object of Schedule Class representing the date and hour of when the flight will take place
     */
    void set_schedule(const Schedule & s1);
    /**
     * method that allows a passenger to be added to the flight
     * checks if there are still empty seats available in the flight
     * @param p object of class Passenger
     * @return returns a boolean value indicating whether it was possible to add the given passenger to the flight
     */
    bool add_passenger(Passenger p);
    /**
     * getter for the number of the flight
     * @return returns integer representing the number/id of the flight
     */
    unsigned get_number() const;
    /**
     * getter for the duration of the flight
     * @return returns object of Time Class representing the duration in hour:minutes of the flight
     */
    Time get_duration() const;
    /**
     * getter for the capacity of the flight
     * @return returns integer representing the capacity of the flight which is equal to the capacity of it's airplane
     */
    unsigned get_capacity () const;
    /**
     * getter for the origin of the flight
     * @return returns string representing the airport where the flight starts
     */
    string get_origin() const;
    /**
     * getter for the destination of the flight
     * @return returns string representing the airport where the flight ends
     */
    string get_destination() const;
    /**
     * getter for all the passengers that checked in the flight
     * @return returns list of passengers containing passengers that will checked in this flight
     */
    list<Passenger> get_passengers() const;
};
;


#endif //AIRLINE_FLIGHT_H