//
// Created by pedro on 05/12/21.
//

#include <iostream>
#include "Airline.h"
#include "Passenger.h"
#include <string>
#include <fstream>

using namespace std;

bool Airline::find_airport(const string &name,Airport * airportptr){
    for (Airport& airport:airports){
        if(airport.get_name()==name) {
            airportptr = &airport;
            return true;
        }
    }
    return false;
}


void Airline::update_flight(Flight & flight){
    char option;
    cout << "1. Change flight Schedule" << endl;
    cout << "2. Add passenger" << endl;
    cin >> option;
    switch(option){
        case '1': {
            Date date;
            Time t;
            cout << "Enter the new date (dd/mm/yyyy): ";
            cin >> date;
            cout << "Enter the time (hh:mm): ";
            cin >> t;
            flight.set_schedule(Schedule(t,date));
            break;
        }
        case '2':{
            string passenger_name;
            char answer;
            cout << "Enter the name of the passenger: ";
            if(cin.peek()=='\n')
                cin.ignore(1);
            getline(cin,passenger_name);
            cout << "Does have have luggagge?(Y/N): ";
            cin >> answer;
            if(answer=='Y')
                flight.add_passenger(Passenger(passenger_name,true));
            else if(answer=='N')
                flight.add_passenger(Passenger(passenger_name,false));
            else
                cout << "Invalid answer" << endl;
            break;
        }
    }
}



Airplane* Airline::find_airplane(const string& license_plate){
    for(Airplane &a1:airplanes){
        if(a1.get_license_plate()==license_plate) {
            return &a1;
        }
    }
    return nullptr;
}

bool Airline::add_flight(Airplane & airplane){
    string origin, destination;
    unsigned flight_number;
    int capacity = airplane.get_capacity();
    cout << "Enter flight number: ";
    cin >> flight_number;
    cout << "Enter date of the flight (day/month/year): ";
    Date d(0,0,0);
    cin >> d;
    cout << "Enter hour of the flight (hour:minute): ";
    Time origin_time(0,0);
    cin >> origin_time;
    Schedule schedule = Schedule(origin_time, d);
    Time duration = Time(0,0);
    cout << "Enter duration of the flight (hour:minute): ";
    cin >> duration;
    cout << "Enter origin location: ";
    cin>> origin;
    Airport * aux;
    if(!find_airport(origin,aux))
        return false;
    cout << "Enter destination location: ";
    cin>>destination;
    if(!find_airport(origin,aux))
        return false;
    Flight f = Flight(capacity, flight_number, duration, schedule, origin, destination);
    airplane.add_flight(f);
    return true;
}

void Airline::update_airplane(Airplane & airplane){
    char option;
    cout << "1. Add flight" << endl;
    cout << "2. Remove flight" << endl;
    cout << "3. Update flight" << endl;
    cout << "4. Check-in luggage" << endl;
    cout << "5. Add Service" << endl;
    cout << "6. Remove Service" << endl;
    cin >> option;
    switch(option){
        case '1':{
            if(add_flight(airplane))
                cout << "Added flight successfully" << endl;
            else
                cout << "No such airport" << endl;
            break;
        }
        case '2': {
            int flight_number;
            cout << "Enter flight number: ";
            cin >> flight_number;

            if(airplane.remove_flight(flight_number))
                cout << "Removed flight successfuly" << endl;
            else
                cout << "No such flight found" << endl;
            break;
        }
        case '3': {
            int flight_number;
            cout << "Enter flight number: ";
            cin >> flight_number;
            Flight *f = airplane.find_flight(flight_number);
            if (f!= nullptr) {
                update_flight(*f);
            }
            else {
                cout << "No such plane with flight number " << flight_number << endl;
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
        case '5': {
            string employee,type;
            cout << "Enter the name of the employee: ";
            cin.ignore(1); // ignores the '\n'
            getline(cin,employee);
            cout << "Enter the type of service (maintenance or cleaning): ";
            cin >> type;
            cout << "Enter date of the service (day/month/year): ";
            Date d(0,0,0);
            cin >> d;
            cout << "Enter hour of the service (hour:minute): ";
            Time t(0,0);
            cin >> t;
            Schedule schedule(t,d);
            if(type=="maintenance"){
                Service service= Service(maintenance, schedule, employee);
                airplane.add_service(service);
            }
            else if(type=="cleaning"){
                Service service= Service(cleaning,schedule, employee);
                airplane.add_service(service);
            }
            else{
                cout << "The type of service that you entered does not exist." << endl;
            }
            break;
        }
        case '6':
            airplane.remove_service();
            break;
        default:
            cout << "The option you entered is invalid." << endl;
    }
}

void Airline::check_airplanes() {

}

void Airline::setup(){


    vector<Time> train_schedules;
    Time current_time(5,45);
    Time past_last_schedule(23,31);
    while(current_time<past_last_schedule){
        train_schedules.push_back(current_time);
        current_time = current_time + Time(0,30);
    }


    vector<Time> subway_schedules;
    current_time.set_hour(6);
    current_time.set_minute(30);
    past_last_schedule.set_hour(23);
    past_last_schedule.set_minute(31);
    while(current_time<past_last_schedule){
        subway_schedules.push_back(current_time);
        current_time = current_time + Time(0,15);
    }


    current_time.set_hour(7);
    current_time.set_minute(0);
    past_last_schedule.set_hour(10);
    past_last_schedule.set_minute(31);
    vector<Time> bus_schedules;
    while(current_time<past_last_schedule){
        bus_schedules.push_back(current_time);
        current_time = current_time + Time(0,15);
    }


    Airport airport_porto (Airport("Porto","Portugal"));
    airport_porto.add_transport(LocalTransport("Campanha",15,"Train",train_schedules));
    airport_porto.add_transport(LocalTransport("Porto Sao Bento",12.5,"Train",train_schedules));
    airport_porto.add_transport(LocalTransport("Campanha",15,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Aeroporto",0.5,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Senhora da Hora",0.5,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Trindade",12,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Barreiro",0.5,"Bus",bus_schedules));
    airport_porto.add_transport(LocalTransport("Campo 24 de Agosto",13,"Bus",bus_schedules));
    airports.push_back(airport_porto);
    Airport airport_lisboa (Airport("Lisboa","Portugal"));
    airport_lisboa.add_transport(LocalTransport("Campo Grande",3,"Subway",subway_schedules));
    airport_lisboa.add_transport(LocalTransport("Campo Grande",3,"Subway",subway_schedules));
    airport_lisboa.add_transport(LocalTransport("Campo Grande",3,"Subway",subway_schedules));
    airport_lisboa.add_transport(LocalTransport("Barreiro",0.5,"Bus",bus_schedules));
    airport_lisboa.add_transport(LocalTransport("Barreiro",0.5,"Bus",bus_schedules));
    airport_lisboa.add_transport(LocalTransport("Santa Apolonia",15,"Train",train_schedules));
    airport_lisboa.add_transport(LocalTransport("Sete Rios",15,"Train",train_schedules));

    airport_lisboa.add_transport(LocalTransport(""));
    airports.push_back(Airport("Lisboa"));
}



void Airline::interface() {
    setup();
    char option;
    while (!cin.eof() and option != '5') {
        cout << "Please enter an option" << endl;
        cout << "1. Add an airplane" << endl;
        cout << "2. Update airplane" << endl;
        cout << "3. Check airplanes" << endl;
        cout << "4. Check near transports" << endl;
        cout << "5. Exit" << endl;
        cin >> option;
        switch (option) {
            case '1': {
                add_airplane();
                break;
            }
            case '2': {
                string license_plate;
                cout << "Enter the airplane's license_plate: ";
                cin >> license_plate;
                Airplane *a1=find_airplane(license_plate);
                if(a1!=nullptr){
                    update_airplane(*a1);
                }
                else{
                    cout << "No such airplane with license plate " << license_plate << endl;
                }
                break;
            }
            case '3':{
                check_airplanes();
                break;
            }
            case '4':{
                string airport_name;
                Airport* ap = nullptr;
                cout << "Enter the airport you are currently in: ";
                cin>>airport_name;
                if(this->find_airport(airport_name,ap)){
                    Time time_now;
                    int n;
                    cout<< "What time is it now: ";
                    cin>>time_now;
                    cout<<"How many transports do you wish to see: ";
                    cin >> n;
                    vector<LocalTransport>nearest_t = ap->get_closest_transports(n);
                    if(nearest_t.size()<n){
                        cout<<"There are only "<< nearest_t.size()<<" transports that are near the airport."<<endl;
                    }
                    for(auto& transport: nearest_t){
                        cout<< transport.get_name()<< "with the next schedule at "<< transport.next_schedules(n,time_now)[0] <<endl;
                    }
                }
                else{
                    cout<< "Invalid Airport Name"<<endl;
                }
                break;
            }
            case '5':{
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
    ifstream file, airplane_file,flight_file;
    file.open("files/Airplanes.txt");
    if(!file.is_open()){
        cerr << "Error opening file Airplanes.txt";
        exit(1);
    }
    string license_plate;
    while(getline(file,license_plate)){
        airplane_file.open("files/Airplane_"+license_plate+".txt");
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
            bool found_services=false;
            airplane_file.ignore(1); // ignores the '\n'
            while(!airplane_file.eof() and airplane_file.peek()!=EOF){
                string aux;
                airplane_file>>aux;
                if (aux=="-----------Services-----------"){
                    found_services=true;
                    break;
                }
                else {
                    flight_number = stoi(aux);
                    flight_file.open("files/Flight_" + to_string(flight_number) + ".txt");
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
                        flight_file.ignore(1); //ignores the '\n'
                        Flight f1 = Flight(flight_capacity, flight_number, duration, schedule, origin, destination);
                        while (!flight_file.eof() and flight_file.peek()!=EOF) {
                            getline(flight_file,passenger_name);
                            flight_file >> luggage;
                            Passenger p1 = Passenger(passenger_name, luggage);
                            f1.add_passenger(p1);
                            flight_file.ignore(1); //ignores the '\n' to move to next line
                        }
                        a1.add_flight(f1);
                    }
                    flight_file.close();
                }
                airplane_file.ignore(1); //"Ignores the \n"
            }
            if(found_services) {
                string employee, type;
                Schedule s;
                while (!airplane_file.eof() and airplane_file.peek()!=EOF) {
                    if(airplane_file.peek()=='\n')
                        airplane_file.ignore(1);
                    getline(airplane_file,employee);
                    airplane_file>>type>>s;
                    if(type=="maintenance"){
                        Service service= Service(maintenance, s, employee);
                        a1.add_service(service);
                    }
                    else{
                        Service service= Service(cleaning, s, employee);
                        a1.add_service(service);
                    }
                    airplane_file.ignore(1);
                }
            }
            airplanes.push_back(a1);
            airplane_file.close();
        }
    }
file.close();
}

Airline::~Airline(){
    ofstream file("files/Airplanes.txt");
    if(!file.is_open()){
        cerr << "Error opening file Airplanes.txt";
        exit(1);
    }
    for(Airplane const& airplane:airplanes){
        file << airplane.get_license_plate() << endl;
        ofstream airplane_file("files/Airplane_"+airplane.get_license_plate()+".txt");
        airplane_file << airplane.get_type() << endl <<
        airplane.get_capacity() << endl;
        for (const Flight& flight:airplane.get_flights()){
            airplane_file << flight.get_number() << endl;
            ofstream flight_file("files/Flight_"+to_string(flight.get_number())+".txt");
            flight_file << flight.get_capacity() << endl << flight.get_duration() << endl
            << flight.get_schedule() << endl <<flight.get_origin() << endl <<flight.get_destination() << endl;
            for(const Passenger&passenger:flight.get_passengers()){
                flight_file << passenger.get_name() << endl << passenger.has_luggage() << endl;
            }
            flight_file.close();
        }
        queue<Service> services = airplane.get_services();
        if(!services.empty()) {
            airplane_file << "-----------Services-----------" << endl;
            while (!services.empty()) {
                Service service = services.front();
                airplane_file << service.get_name() << endl << (service.get_type() ? "cleaning" : "maintenance") << endl
                     << service.get_schedule() << endl;
                services.pop();
            }
        }
        airplane_file.close();
    }
    file.close();
};