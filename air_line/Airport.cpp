//
// Created by Pedro on 14/12/2021.
//

#include "Airport.h"

Airport::Airport(const string &name):name(name),transports(LocalTransport("",0.0,"",vector<Time>())) {
}


string Airport::get_name() const{
    return name;
}
void Airport::set_name(const string & name){
    this->name = name;
}
bool Airport::add_transport(const LocalTransport &lt){
    return transports.insert(lt);
}
bool Airport::remove_transport (const LocalTransport &lt){
    return transports.remove(lt);
}

vector<LocalTransport> Airport::get_closest_transports(unsigned n_closest){
    BSTItrIn<LocalTransport> itr(transports);
    vector<LocalTransport> nearest_transports;
    while(!itr.isAtEnd() and n_closest>0){
        nearest_transports.push_back(itr.retrieve());
        n_closest--;
    }
    return nearest_transports;
}