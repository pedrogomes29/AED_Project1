//
// Created by pedro on 05/12/21.
//

#include <iostream>
#include "Airline.h"
#include "Passenger.h"
#include <string>
#include <fstream>
#include <sys/stat.h>

using namespace std;

void Airline::interface() {
    char option;
    while(!cin.eof() and option!='5') {
        cout << "Please enter an option" << endl;
        cout << "1. Add an airplane" << endl;
        cout << "2. Update airplane" << endl;
        cout << "3. Check airplanes" << endl;
        cout << "4. Exit" << endl;
        cin >> option;
        switch(option){
            case '1':
                add_airplane();
                break;
            case '2':
                update_airplane();
                break;
            case '3':
                check_airplanes();
            default:
                cout << "The option you intered is invalid" << endl;
        }
    }
}

void Airline::update_airplane(){
    cout << "1. Add flight" << endl;
    cout << "2. Remove flight" << endl;
    cout << "3. Update flight" << endl;
    cout << "4. Check-in luggage" << endl;
    cout << "5. Add Service" << endl;
    cout << "6. Remove Service" << endl;
}

void Airline::update_flight(){
    cout << "1. Change flight time" << endl;
    cout << "2. Add passenger" << endl;
}

void Airline::add_passenger(){
    cout << "Enter the name of the passenger: ";
    string name,answer;
    bool luggage;
    getline(cin,name);
    cout << "Does he/she have luggage?";
    cin >> answer;
    (answer=="yes")?luggage=true:luggage=false;
    while(!flight.add_passenger(Passenger(name,luggage)));
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
            while(airplane_file.eof()){
                airplane_file>>flight_number;
                flight_file.open("Flight_"+ to_string(flight_number)+".txt");
                if(!flight_file.is_open()) {
                    cerr << "Error opening file of flight number " << flight_number << endl;
                    exit(1);
                }
                else{
                    unsigned flight_capacity;
                    Time duration;
                    Schedule schedule;
                    string origin, destination;
                    vector<Passenger> passengers;
                    while(!flight_file.eof()){
                        flight_file>>flight_capacity>>duration>>schedule>>origin>>destination;
                        Flight f1= Flight(flight_capacity,flight_number,duration,schedule,origin,destination);
                        a1.add_flight(f1);
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
        cout << "---------EndOfAirplane---------" << endl;
    }
};