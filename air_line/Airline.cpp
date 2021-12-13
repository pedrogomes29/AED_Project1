//
// Created by pedro on 05/12/21.
//

#include <iostream>
#include "Airline.h"
#include "Passenger.h"
#include <string>
#include <fstream>

using namespace std;

void Airline::update_flight(Flight & flight){
    cout << "1. Change flight time" << endl;
    cout << "2. Add passenger" << endl;
}

void Airline::add_passenger(Flight & flight){
    cout << "Enter the name of the passenger: ";
    string name,answer;
    bool luggage;
    getline(cin,name);
    cout << "Does he/she have luggage?";
    cin >> answer;
    (answer=="yes")?luggage=true:luggage=false;
    while(!flight.add_passenger(Passenger(name,luggage)));
}


Airplane& Airline::find_airplane(const string& license_plate){
    Airplane default_airplane = Airplane("","",0);
    for(Airplane &a1:airplanes){
        if(a1.get_license_plate()==license_plate)
            return a1;
    }
    return default_airplane;
}

void add_flight(Airplane & airplane){
    string origin, destination;
    unsigned flight_number;
    char sep;
    int hour, minute,day,month,year;
    int origin_hour, origin_minute;
    int capacity = airplane.get_capacity();
    cout << "Enter flight number: ";
    cin >> flight_number;
    cout << "Enter date of the flight (day/month/year): ";
    cin >> day >> sep >> month >> year;
    Date d = Date(day, month, year);
    cout << "Enter hour of the flight (hour:minute): ";
    cin >> origin_hour>> sep >> origin_minute;
    Time origin_time = Time(origin_hour, origin_minute);
    Schedule schedule = Schedule(origin_time, d);
    cout << "Enter duration of the flight (hour:minute): ";
    cin >> hour >> sep >> minute;
    Time duration = Time(hour, minute);
    cout << "Enter origin location ";
    cin>> origin;
    cout << "Enter destination location: ";
    cin>>destination;
    Flight f = Flight(capacity, flight_number, duration, schedule, origin, destination);
    airplane.add_flight(f);
}

void Airline::update_airplane(Airplane & airplane){
    char option;
    cout << "1. Add flight" << endl;
    cout << "2. Remove flight" << endl;
    cout << "3. Update flight" << endl;
    cout << "4. Check-in luggage" << endl;
    cout << "5. Add Service" << endl;
    cout << "6. Remove Service" << endl;
    switch(option){
        case '1':{
            add_flight(airplane);
            break;
        }
        case '2': {
            int flight_number;
            cout << "Enter flight number: ";
            cin >> flight_number;
            if(airplane.remove_flight(flight_number))
                cout << "Removed airplane successfuly" << endl;
            else
                cout << "No such airplane found" << endl;
            break;
        }
        case '3': {
            int flight_number;
            cout << "Enter flight number: ";
            cin >> flight_number;
            Flight &f = airplane.find_flight(flight_number);
            if (f.get_destination() == "") //Invalid airplane found
                cout << "Flight with number " << flight_number << "not found." << endl;
            else {
                update_flight(f);
            }
            break;
        }
        case '4': {
            string employee, type;
            Schedule schedule;
            Service service(maintenance,"",0,0,"");
            cout << "Enter the employee name: ";
            cin >> employee;
            cout << "Enter the type of service (maintenance or cleaning)";
            if (type == "maintenance") {
                service = Service(maintenance, schedule, employee);
            } else if (type == "cleaning") {
                service = Service(cleaning, schedule, employee);
            } else {
                cout << "No such type of service." << endl;
                break;
            }
            if (airplane.add_service(service))
                cout << "Service added successfuly" << endl;
            else
                cout << "Failed to add service (flight conflict)" << endl;
            break;
        }
        case '5':

            break;
        case '6':

            break;
        default:
            cout << "The option you entered is invalid." << endl;
    }
}

void Airline::check_airplanes() {

}

void Airline::interface() {
    char option;
    while (!cin.eof() and option != '5') {
        cout << "Please enter an option" << endl;
        cout << "1. Add an airplane" << endl;
        cout << "2. Update airplane" << endl;
        cout << "3. Check airplanes" << endl;
        cout << "4. Exit" << endl;
        cin >> option;
        switch (option) {
            case '1': {
                add_airplane();
                break;
            }
            case '2': {
                string license_plate;
                cout << "Enter the airplane's license_plate: ";
                Airplane & a1 = find_airplane(license_plate);
                if(a1.get_license_plate()==""){
                    cout << "No such airplane with license plate " << license_plate << endl;
                }
                else{
                    update_airplane(a1);
                }
                break;
            }
            case '3':{
                check_airplanes();
                break;
            }
            case '4':{
                continue;
            }
            default:{
                cout << "The option you entered is invalid. " << endl;
                break;
            }
        }
    }
}

void Airline::add_airplane() {
    string license_plate,type;
    unsigned capacity;
    cout << "Enter license plate: ";
    cin >> license_plate;
    cout << "Enter airplane type: ";
    cin >> type;
    cout << "Enter airplane capacity: ";
    cin >> capacity;
    airplanes.push_back(Airplane(license_plate,type,capacity));
}


Airline::Airline(){
    fstream file, airplane_file,flight_file;
    file.open("Airplanes.txt");
    if(!file.is_open()){
        cerr << "Error opening file Airplanes.txt";
        exit(1);
    }
    string license_plate;
    while(getline(file,license_plate)){
        airplane_file.open("Airplane_"+license_plate+".txt");
        if(!airplane_file.is_open()) {
            cerr << "Error opening airplane file with license plate " <<license_plate<<endl;
            exit(1);
        }
        else{
            string type;
            unsigned capacity,flight_number;
            airplane_file>>type;
            airplane_file>>capacity;
            Airplane a1 = Airplane(license_plate,type,capacity);
            airplanes.push_back(a1);
            bool found_services=false;
            while(!airplane_file.eof()){
                string aux;
                airplane_file>>aux;
                if (aux=="-----------Services-----------"){
                    found_services=true;
                    break;
                }
                else {
                    flight_number = stoi(aux);
                    flight_file.open("Flight_" + to_string(flight_number) + ".txt");
                    if (!flight_file.is_open()) {
                        cerr << "Error opening file of flight number " << flight_number << endl;
                        exit(1);
                    } else {
                        unsigned flight_capacity;
                        Time duration;
                        Schedule schedule;
                        string origin, destination, passenger_name;
                        bool luggage;
                        flight_file >> flight_capacity >> duration >> schedule >> origin >> destination;
                        Flight f1 = Flight(flight_capacity, flight_number, duration, schedule, origin, destination);
                        while (!flight_file.eof()) {
                            flight_file >> passenger_name >> luggage;
                            Passenger p1 = Passenger(passenger_name, luggage);
                            f1.add_passenger(p1);
                        }
                        a1.add_flight(f1);
                    }
                }
            }
            if(found_services) {
                string employee, type;
                Schedule s;
                while (!airplane_file.eof()) {
                    airplane_file>> employee>>type>>s;
                    if(type=="maintenance"){
                        Service service= Service(maintenance, s, employee);
                        a1.add_service(service);
                    }
                    else{
                        Service service= Service(cleaning, s, employee);
                        a1.add_service(service);
                    }
                }
            }
        }
    }

}

Airline::~Airline(){
    ofstream file;
    file.open("Airplanes.txt");
    if(!file.is_open()){
        cerr << "Error opening file Airplanes.txt";
        exit(1);
    }
    for(Airplane const& airplane:airplanes){
        file << airplane.get_license_plate() << endl;
        ofstream airplane_file("Airplane_"+airplane.get_license_plate()+".txt");
        airplane_file << airplane.get_type() << endl <<
        airplane.get_capacity() << endl;
        for (const Flight& flight:airplane.get_flights()){
            airplane_file << flight.get_number() << endl;
            ofstream flight_file("Flight_"+to_string(flight.get_number())+".txt");
            flight_file << flight.get_capacity() << endl << flight.get_duration() << endl
            << flight.get_schedule() << endl <<flight.get_origin() << endl << endl <<flight.get_destination() << endl;
            for(const Passenger&passenger:flight.get_passengers()){
                flight_file << passenger.get_name() << " " << passenger.has_luggage();
            }
        }
        cout << "-----------Services-----------" << endl;
        queue<Service> services = airplane.get_services();
        while(!services.empty()){
            Service service = services.front();
            cout << service.get_name() << " " << (service.get_type()? "cleaning":"maintenance") << " " <<service.get_schedule() << endl;
            services.pop();
        }
    }
};