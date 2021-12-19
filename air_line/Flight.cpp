//
// Created by rui on 01/12/21.
//

#include "Flight.h"

const unsigned INVALID = -1;

unsigned read_unsigned() {
    unsigned n;
    cin >> n;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
        return INVALID;
    }
    else if (cin.fail() or cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return n;
}




Flight::Flight() {
    this->capacity = 0;
    this->number = 0;
    this->duration = Time(0,0);
    this->schedule = Schedule(Time(0,0),Date(0,0,0));
    this-> origin = "";
    this->destination = "destination";
}

Flight::Flight(unsigned capacity,unsigned number,Time duration,const string& date_of_departure, unsigned hour,unsigned minute, string origin,
       string destination, list<Passenger> passengers){
this->capacity = capacity;
this->number = number;
this->duration = duration;
this->schedule = Schedule(Time(hour,minute),Date(date_of_departure));
this-> origin = origin;
this->destination = destination;
this-> passengers = passengers;
}

Flight::Flight(unsigned capacity,unsigned number,Time duration,Schedule schedule,string origin,string destination){
    this->capacity = capacity;
    this->number = number;
    this->duration = duration;
    this->schedule = schedule;
    this-> origin = origin;
    this->destination = destination;
}


Schedule Flight::get_schedule() const {
    return schedule;
}
bool Flight::add_passenger(Passenger p) {
    if(passengers.size()<capacity){
        passengers.push_back(p);
        return true;
    }
    return false;
}

/**
 *
 * prints the car given as a paramater to the screen
 * @param vector1 carriages to print
 */

void print_carriages(vector<vector<stack<string>>> vector1) {
    bool nothing_more_to_print=false;
    for(int i = 0; i<vector1.size();i++){
        if(nothing_more_to_print)
            break;
        for(int j=0;j<vector1[0].size();j++){
            if(vector1[i][j].empty()) {
                nothing_more_to_print = true;
                break;
            }
            cout <<"-------------"<< endl;
            while(!vector1[i][j].empty()) {
                cout << vector1[i][j].top() << endl;
                vector1[i][j].pop();
            }
            cout <<"-------------"<< endl;
        }
        cout << endl;
    }
    cout << endl;
}

void Flight::show_baggages()const{
    bool there_is_luggage=false;
    unsigned num_of_carriages=-1, num_of_stacks=-1, stack_size=-1;
    while(num_of_carriages==(unsigned)-1) {
        cout << "Enter the number of carriages: ";
        num_of_carriages = read_unsigned();
    }
    while(num_of_stacks==(unsigned)-1) {
        cout << "Enter the number of stacks: ";
        num_of_stacks = read_unsigned();
    }
    while(stack_size==(unsigned)-1) {
        cout << "Enter the stack size: ";
        stack_size = read_unsigned();
    }
    vector<vector<stack<string>>> carriages(num_of_carriages, vector<stack<string>>(num_of_stacks));
    unsigned trips=1;
    unsigned carriage=0;
    unsigned pile=0;
    unsigned current_size=0;
    for(const Passenger& p:passengers){
        if(p.has_luggage()){
            if(!there_is_luggage)
                there_is_luggage=true;
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
    if(there_is_luggage) {
        if (trips > 1)
            cout << "The car made " << trips << " trips." << endl;
        else
            cout << "The car made " << trips << " trip." << endl;
    }
    else
        cout << "No luggage found" << endl;
}



unsigned Flight::get_number() const {
    return number;
}

Time Flight::get_duration() const {
    return duration;
}

string Flight::get_origin() const{
    return origin;
}

string Flight::get_destination() const {
    return destination;
}

list<Passenger> Flight::get_passengers() const {
    return passengers;
}

unsigned Flight::get_capacity () const{
    return capacity;
}


