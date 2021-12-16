//
// Created by Pedro on 14/12/2021.
//

#include "Airport.h"

Airport::Airport(const string &name,const string&country):name(name),country(country),transports(LocalTransport("",0.0,"",vector<Time>())) {


}
string Airport::get_country() const {
    return country;
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

BST<LocalTransport> Airport::get_transports()const {
    return transports;
}

const LocalTransport* Airport::find_transport(const string&transport_name, const string& type)const{
    BSTItrIn<LocalTransport> itr(transports);
    while(!itr.isAtEnd()){
        if(itr.retrieve().get_type()==type and itr.retrieve().get_name()==transport_name){
            return &itr.retrieve();
        }
        itr.advance();
    }
    return nullptr;
}


vector<LocalTransport> Airport::get_closest_transports(unsigned n_closest) const{
    BSTItrIn<LocalTransport> itr(transports);
    vector<LocalTransport> nearest_transports;
    while(!itr.isAtEnd() and n_closest>0){
        nearest_transports.push_back(itr.retrieve());
        n_closest--;
        itr.advance();
    }
    return nearest_transports;
}