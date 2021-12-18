//
// Created by Pedro on 14/12/2021.
//

#ifndef AIRLINE_AIRPORT_H
#define AIRLINE_AIRPORT_H
#include <string>
#include <vector>
#include "BST.h"
#include "Schedule.h"
#include "LocalTransport.h"

using namespace std;

class Airport {

private:
    string name;
    string country;
    BST<LocalTransport> transports;
public:
    /**
     * Constructor of the Airport class
     * @param name string representing the name of the Airport
     * @param country string representing the country where the airport is located
     */
    Airport(const string& name,const string &country);
    /**
     * getter for the name attribute
     * @return returns string representing the name of the Airport
     */
    string get_name() const;
    /**
     * getter for the country attribute
     * @return returns string representing the country where the airport is located
     */
    string get_country() const;
    /**
     * method which allows us to insert a local transport near the airport in the bst transports
     * @param lt object of LocalTransport class which we want to insert in the bst transports
     * @return returns a boolean value indicating whether it was possible to complete the insertion
     */
    bool add_transport(const LocalTransport &lt);
    /**
     * method which allows us to remove a local transport near the airport from the bst transports
     * @param lt object of LocalTransport class which we want to remove from the bst transports
     * @return returns a boolean value indicating whether it was possible to complete the removal
     */
    bool remove_transport (const LocalTransport &lt);
    /**
     * Method which shows the user the 'n' closest local transports to the airport in which the user is currently at
     * @param n_closest unsigned int representing the number of local transports the user wishes to see
     * @return returns a vector of LocalTransport objects of size n that are sorted by closest distance to the airport
     */
    vector<LocalTransport> get_closest_transports(unsigned n_closest) const;
    /**
     * getter for the transports attribute
     * @return returns the BST of LocalTransport objects near the airplane
     */
    BST<LocalTransport> get_transports()const;
    /**
     * Method that searches the bst for a transport with the same name and type as the arguments.
     * @param name string passed by reference representing the name of the transport we want to find
     * @param type string passed by reference representing the type of transport we want to find
     * @return returns a pointer to the Local Transport the user wanted to find else returns a null pointer
     */
    const LocalTransport* find_transport(const string&name, const string& type)const;
};




#endif //AIRLINE_AIRPORT_H
