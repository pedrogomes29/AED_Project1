//
// Created by pedro on 01/12/21.
//

#include <iostream>
#include <stack>
#include "Airplane.h"


Airplane::Airplane() {
    license_plate = "";
    type = "";
    capacity= 0;
};

Airplane::Airplane(string _license_plate,string _type,unsigned _capacity){
    license_plate = _license_plate;
    type=_type;
    capacity=_capacity;
}

Schedule result(Schedule s,Time t){
    int min = s.get_time().get_minute()+t.get_minute();
    int hour = s.get_time().get_hour()+t.get_hour();
    Date d = s.get_date();
    if(min>60){
        min = min%60;
        hour+=hour/60;
    }
    if(hour>23){
        d.increment(hour/24);
        hour%=24;
    }
    return Schedule(Time(hour,min),d);
}


/*

bool Airplane::add_flights(const vector<Flight> &flights){
    if(flights.empty()){
        flights.push_back(flights[0]);
        return true;
    }
    for(auto iter=flights.begin(); iter!= flights.end();iter++){
        if(flights[0].get_schedule() < (*iter).get_schedule()) {
            flights.insert(iter, flights[0]);
            return true;
        }
    }
    flights.push_back(f);
}
*/
bool Airplane::add_service(const Service& serv) {
    if(flights.empty()){
        services.push(serv);
        return true;
    }
    Time duration = serv.get_duration();
    Schedule s = serv.get_schedule();
    Schedule s_f = result(s,duration);
    for(auto const &f:flights){
        if(s<f.get_schedule() && f.get_schedule()<s_f )
            return false;
        if(s<f.get_schedule() && f.get_schedule()<s_f)
            return false;
        if (f.get_schedule() < s && s< result(f.get_schedule(),f.get_duration()))
            return false;
    }
    services.push(serv);
    return true;
}



bool Airplane::remove_flight(unsigned number){
    for (auto iter = flights.begin();iter!=flights.end();iter++){
        if(iter->get_number()==number){
            bool is_about_to_happen;
            cout << "Do you want to cancel the flight or is it about to happen? (0 to cancel else 1): ";
            cin >> is_about_to_happen;
            if(is_about_to_happen) {
                iter->show_baggages();
            }
            remove(("files/Flight_"+to_string(iter->get_number())+".txt").c_str());
            flights.erase(iter);
            return true;
        }
    }
    return false;
}


Flight* Airplane::find_flight(unsigned number){
    int low = 0;
    int high = flights.size()-1;
    while(low<=high){
        int middle = (low+high)/2;
        if (flights[middle].get_number()<number)
            low=middle+1;
        else if(number<flights[middle].get_number())
            high=middle-1;
        else{
            return &flights[middle];
        }
    }
    return nullptr;
}

string Airplane::get_license_plate() const {
    return license_plate;
}

string Airplane::get_type() const{
    return type;
}
unsigned Airplane::get_capacity() const{
    return capacity;
};
queue<Service> Airplane::get_services() const{
    return services;
};
vector<Flight> Airplane::get_flights() const{
    return flights;
}

bool Airplane::remove_service() {
    if(services.empty()) return false;
    services.pop();
    return true;
}

