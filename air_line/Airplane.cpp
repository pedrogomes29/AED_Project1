//
// Created by pedro on 01/12/21.
//

#include <iostream>
#include <stack>
#include "Airplane.h"

const char INVALID_KEY = 0;

char read_char() {
    char c;
    cin >> c;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
        return INVALID_KEY;
    }
    else if (cin.peek() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_KEY;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return c;
}



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


queue<Service> Airplane::get_services() const{
    return services;
}


bool Airplane::check_if_in_order_removing(const vector<Flight> &flights){
    for(unsigned int i=1;i<flights.size();i++){
        Schedule previous_arrival = flights[i - 1].get_schedule();
        previous_arrival.add_time(flights[i - 1].get_duration());
        if (flights[i].get_origin() != flights[i - 1].get_destination() ||
        flights[i].get_schedule() < previous_arrival)
             return false;
    }
    return true;
}


bool Airplane::check_if_in_order_adding(const vector <Flight> &flights) const{
    queue<Service> aux_services = get_services();
    vector<Service> v_services;
    while(!aux_services.empty()){
        v_services.push_back(aux_services.front());
        aux_services.pop();
    }
    for(unsigned int i=0;i<flights.size();i++){
        Schedule arrival = flights[i].get_schedule();
        arrival.add_time(flights[i].get_duration());
        if(i>=1) {
            if (flights[i].get_origin() != flights[i - 1].get_destination() ||
                flights[i].get_schedule() < arrival)
                return false;
        }
        for(const Service& s:v_services){
            Schedule end_service = s.get_schedule();
            end_service.add_time(s.get_duration());
            if((s.get_schedule()<flights[i].get_schedule() and flights[i].get_schedule()<end_service ||
            flights[i].get_schedule()<s.get_schedule() and s.get_schedule()<arrival))
                return false;
        }
    }
    return true;
}


bool Airplane::add_flights(vector<Flight> new_flights){
    auto previous=flights.begin();
    auto iter = flights.begin();
    if(flights.empty()){
        if(check_if_in_order_adding(new_flights)) {
            flights = new_flights;
            return true;
        }
    }
    bool insert_in_end=true;
    bool insert_in_beggining=true;
    for(iter; iter!= flights.end();iter++){
        if(new_flights[0].get_schedule()<iter->get_schedule()){
            insert_in_end=false;
            break;
        }
        else if (insert_in_beggining)
            insert_in_beggining=false;
        previous = iter;
    }
    if(!insert_in_beggining)
        new_flights.insert(new_flights.begin(), *previous);
    if(!insert_in_end)
        new_flights.push_back(*iter);
        if(check_if_in_order_adding(new_flights)){
        unsigned i,end;
        if(insert_in_beggining)
            i=0;
        else
            i=1;
        if(insert_in_end)
            end = new_flights.size();
        else
            end = new_flights.size()-1;
        for(i;i<end;i++){
            iter = flights.insert(iter,new_flights[i]);
            iter++;
        }
        return true;
    }
    return false;

}

bool Airplane::add_service(const Service& serv) {
    if(flights.empty()){
        services.push(serv);
        return true;
    }
    Time duration = serv.get_duration();
    Schedule s = serv.get_schedule();
    Schedule end_service = s;
    end_service.add_time(duration);
    for(auto const &f:flights){
        Schedule arrival = f.get_schedule();
        arrival.add_time(f.get_duration());
        if(s<f.get_schedule() && f.get_schedule()<end_service)
            return false;
        if (f.get_schedule() < s && s<arrival)
            return false;
    }
    services.push(serv);
    return true;
}


void Airplane::add_flight(const Flight &f){
    flights.push_back(f);
}

void Airplane::start_flight(){
        flights[0].show_baggages();
        remove(("files/Flight_"+to_string(flights[0].get_number())+".txt").c_str());
        flights.erase(flights.begin());
}

bool is_in(unsigned number,const vector<unsigned>&numbers){
    for(unsigned n:numbers){
        if (n==number)
            return true;
    }
    return false;
}



bool Airplane::cancel_flights(const vector<unsigned>& numbers){
    unsigned flights_found=0;
    vector<Flight> aux_vector;
    for(const Flight &f:flights){
        if (!is_in(f.get_number(),numbers))
            aux_vector.push_back(f);
        else{
            flights_found++;
        }
    }
    if(flights_found<numbers.size())
        return false;
    else if(check_if_in_order_removing(aux_vector)) {
        for(unsigned n:numbers) {
            remove(("files/Flight_" + to_string(n) + ".txt").c_str());
        }
        flights = aux_vector;
        return true;
    }
    else{
        return false;
    }
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

vector<Flight> Airplane::get_flights() const{
    return flights;
}

bool Airplane::remove_service() {
    if(services.empty()) return false;
    services.pop();
    return true;
}

