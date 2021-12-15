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

void Airplane::add_flight(const Flight &f){
    flights.push_back(f);
}

void Airplane::update_flights(){
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    Schedule time_now(Time(now->tm_hour,now->tm_min),Date(now->tm_mday,now->tm_mon+1,now->tm_year+1900));
    auto iter = flights.begin();
    while(iter->get_schedule()<time_now and iter!=flights.end()){
        auto aux = iter;
        iter++;
        flights.erase(aux);
    }
}


bool Airplane::add_service(Service serv) {
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

bool find_next_stack(vector<vector<stack<string>>> carriages,unsigned stack_size,unsigned & carriage,unsigned &pile){
    for(unsigned carriage_index=0;carriage_index<carriages.size();carriage_index++){
        for(unsigned pile_index=0;pile_index<carriages[0].size();pile_index++){
            if(carriages[carriage_index][pile_index].size()<stack_size) {
                carriage=carriage_index;
                pile=pile_index;
                return true;
            }
        }
    }
    return false;
}
void print_carriages(vector<vector<stack<string>>> vector1) {
    for(int i = 0; i<vector1.size();i++){
        for(int j=0;j<vector1[0].size();j++){
            while(!vector1[i][j].empty()) {
                cout << vector1[i][j].top() << endl;
                vector1[i][j].pop();
            }
        }
    }
}




void show_baggages(Flight f){
    unsigned num_of_carriages, num_of_stacks, stack_size;
    cout << "Enter the number of carriages: ";
    cin >> num_of_carriages;
    cout << "Enter the number of stacks: ";
    cin >> num_of_stacks;
    cout << "Enter the stack size: ";
    cin >> stack_size;
    vector<vector<stack<string>>> carriages(num_of_carriages, vector<stack<string>>(num_of_stacks));
    vector<Passenger> passengers = f.get_passengers();
    for(Passenger p:passengers){
        if(p.has_luggage()){
            unsigned carriage;
            unsigned pile;
            if(!find_next_stack(carriages,stack_size,carriage,pile)) {
                print_carriages(carriages);
                carriages = vector<vector<stack<string>>>(num_of_carriages,vector<stack<string>>(num_of_stacks)); // clears carriages
            }
            else{
                carriages[carriage][pile].push(p.get_name());
            }
        }
    }
    if(!carriages[0][0].empty()) // if  first pile in first stack is empty(there's something to print)
        print_carriages(carriages);
    return;
}


bool Airplane::remove_flight(unsigned number){
    for (auto iter = flights.begin();iter!=flights.end();iter++){
        if(iter->get_number()==number){
            bool is_about_to_happen;
            cout << "Do you want to cancel the flight or is it about to happen? (0 to cancel else 1): ";
            cin >> is_about_to_happen;
            if(is_about_to_happen) {
                show_baggages(*iter);
            }
            remove(("files/Flight_"+to_string(iter->get_number())+".txt").c_str());
            flights.erase(iter);
            return true;
        }
    }
    return false;
}


Flight* Airplane::find_flight(unsigned number){
    for(Flight &f:flights){
        if(f.get_number()==number) {
            return &f;
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
list<Flight> Airplane::get_flights() const{
    return flights;
}

bool Airplane::remove_service() {
    if(services.empty()) return false;
    services.pop();
    return true;
}
