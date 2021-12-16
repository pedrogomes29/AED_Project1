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
    if(flights.empty())flights.push_back(f);
    for(auto iter=flights.begin(); iter!= flights.end();iter++){
        if(f.get_schedule() < (*iter).get_schedule()) {
            flights.insert(iter, f);
            return;
        }
    }
    flights.push_back(f);
}

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

/*
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
 */
void print_carriages(vector<vector<stack<string>>> vector1) {
    for(int i = 0; i<vector1.size();i++){
        for(int j=0;j<vector1[0].size();j++){
            while(!vector1[i][j].empty()) {
                cout << vector1[i][j].top() << endl;
                vector1[i][j].pop();
            }
        }
    }
    cout << endl;
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
    list<Passenger> passengers = f.get_passengers();
    unsigned trips=1;
    unsigned carriage=0;
    unsigned pile=0;
    unsigned current_size=0;
    for(Passenger p:passengers){
        if(p.has_luggage()){
            current_size++;
            if(current_size>stack_size) {
                current_size = 1;
                pile++;
            }
            if(pile>=num_of_stacks){
                carriage++;
                pile=0;
            }
            if(carriage>=num_of_carriages) {
                trips++;
                carriage=0;
                pile=0;
                current_size=1;
                print_carriages(carriages);
                carriages = vector<vector<stack<string>>>(num_of_carriages,vector<stack<string>>(num_of_stacks));// clears carriages
                carriages[0][0].push(p.get_name());
            }
            else{
                carriages[carriage][pile].push(p.get_name());
            }
        }
    }
    if(!carriages[0][0].empty()) // if  first pile in first stack isn't empty(there's something to print)
        print_carriages(carriages);
    cout << "The car made " << trips << " trips." << endl;
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

