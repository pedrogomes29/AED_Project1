//
// Created by Rui on 14/12/2021.
//

#ifndef AIRLINE_LOCALTRANSPORT_H
#define AIRLINE_LOCALTRANSPORT_H

#include "Time.h"
#include <string>
#include <vector>

using namespace std;

class LocalTransport {
private:
    string name;
    float distance;
    string type;
    vector<Time> schedules;
public:
    /**
     * Default constructor of LocalTransport class
     * Default local Transport is a local transport
     * of name "" distance = 0 and type = ""
     * with no schedules
     */
    LocalTransport();
    /**
     * Constructor of class LocalTransport
     * @param name string representing the name of the LocalTransport
     * @param distance float indicating the distance of an airport to this localTransport
     * @param type string representing either train a subway or a bus.
     * @param schedules ordered vector of schedules that store the schedules of this particular LocalTransport
     */
    LocalTransport(string name,float distance,string type,vector<Time> schedules);
    /**
     * getter for the name attribute
     * @return returns a string representing the name of the LocalTransport
     */
    string get_name() const;
    /**
     * setter for the name of the LocalTransport
     * @param name string representing the name of the LocalTransport
     */
    void set_name(string name);
    /**
     * getter for the distance attribute
     * @return returns float indicating the distance of an airport to this localTransport
     */
    float get_distance() const;
    /**
     * setter for the distance attribute
     * @param d float indicating the distance of an airport to this localTransport
     */
    void set_distance(float &d);
    /**
     * getter for the type attribute
     * @return returns a string representing the type of the LocalTransport
     */
    string get_type() const;
    /**
     * setter for the type attribute
     * @param t string representing the type of the LocalTransport
     */
    void set_type(string &t);
    /**
     * getter for all the schedules of this LocalTransport
     * @return returns ordered vector of schedules that store the schedules of this particular LocalTransport
     */
    vector<Time> get_schedules() const;
    /**
     * setter for all the schedules of this LocalTransport
     * @param s ordered vector of schedules that store the schedules of this particular LocalTransport
     */
    void set_schedules(vector<Time> &s);
    /**
     * Adds an object of class Schedule t to the ordered vector schedules in the correct
     * @param s
     */
    void add_schedule(Time s);
    /**
     * Overloading of the < operator used to compare two LocalTransport.
     * @param lt1 object of class LocalTransport passed by reference.
     * @return returns a boolean value indicating whether this local transport is lesser than lt1. We compare them by distance to the airport
     */
    bool operator<(const LocalTransport &lt1) const;
    /**
     *
     * @param n integer representing the number of schedules the user wishes to see
    * @param t object of class time that represents the lower time limit for the desired schedules output that the user wants to see.
    * @return returns ordered vector containing n schedules after the time t given by by the user.
     */
    vector<Time> next_schedules(int n, Time t)const;

};



#endif //AIRLINE_LOCALTRANSPORT_H
