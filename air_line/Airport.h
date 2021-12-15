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
    string get_name() const;
    void set_name(const string &name);
    bool add_transport(const LocalTransport &lt);
    bool remove_transport (const LocalTransport &lt);
    vector<LocalTransport> get_closest_transports(unsigned n_closest);
    Airport(const string& name, const string& country);
};




#endif //AIRLINE_AIRPORT_H
