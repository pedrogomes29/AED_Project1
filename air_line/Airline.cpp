//
// Created by pedro on 05/12/21.
//

#include <iostream>
#include "Airline.h"
#include "Passenger.h"
#include <string>
#include <fstream>


using namespace std;

const char INVALID_KEY = 0;

const int INVALID = -1;

const Date INVALID_DATE = Date(0,0,0);
const string INVALID_STRING = "";
const Time INVALID_TIME = Time (0,0);

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

char readChar() {
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


string read_string(){
    string s;
    cin >> s;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
        return INVALID_STRING;
    }
    else if (cin.peek() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_STRING;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return s;
}

int read_int() {
    int n;
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
Date read_date(){
    Date d;
    cin >> d;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
        return INVALID_DATE;
    }
    else if (cin.fail() or cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_DATE;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return d;
}

Time read_time(){
    Time t;
    cin >> t;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
        return INVALID_TIME;
    }
    else if (cin.fail() or cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_TIME;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return t;
}

unsigned readUnsigned() {
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


void Airline::interface() {
    setup();
    char option;
    while (!cin.eof() and option != '5') {
        cout<<endl;
        cout << "Please enter an option" << endl;
        cout << "1. Add an airplane" << endl;
        cout << "2. Update airplane" << endl;
        cout << "3. Check Database" << endl;
        cout << "4. Check near transports" << endl;
        cout << "5. Exit" << endl;
        cout<<endl;
        option=readChar();
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
                check_db();
                break;
            }
            case '4':{
                string airport_name;
                cout << "Enter the airport you are currently in: ";
                while(airport_name=="")
                    airport_name = read_string();
                Airport* ap = find_airport(airport_name);
                if(ap!=nullptr){
                    check_new_transports(*ap);
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

bool Airline::add_airplane() {
    string license_plate,type;
    unsigned capacity;
    while(license_plate.empty()) {
        cout << "Enter license plate (no spaces allowed): ";
        license_plate = read_string();
    }
    while(type.empty()) {
        cout << "Enter airplane type (no spaces allowed): ";
        type = read_string();
    }
    cout << "Enter airplane capacity: ";
    capacity = readUnsigned();
    Airplane airplane(license_plate,type,capacity);
    auto iter = airplanes.begin();
    for(iter;iter!=airplanes.end();iter++){
        if(iter->get_license_plate()>airplane.get_license_plate())
            break;
        else if(iter->get_license_plate()==airplane.get_license_plate())
            return false;
    }
    airplanes.insert(iter,airplane);
    return true;
}

void Airline::check_db() {
    char option;
    while(!cin.eof() and option!='5') {
        cout << endl;
        cout << "1. See the soonest 'x' flights. " << endl;
        cout << "2. See every plane owned by this airline company. " << endl;
        cout << "3. See every airport we operate in. " << endl;
        cout << "4. See all flights to a specific destination from a specific origin. "<<endl;
        cout << "5. Exit to previous menu. " << endl;
        cout << "Option: ";
        option=readChar();
        switch (option) {
            case '1': {
                int n;
                cout << "How many flights do you wish to see: ";
                n = read_int();
                    print_soonest_flights(n);
                break;
            }
            case '2': {
                char answer;
                cout << "Sort planes by :" << endl;
                cout << "A. License Plate" << endl;
                cout << "B. Type" << endl;
                cout << "C. Capacity" << endl;
                cout << "Option: ";
                cin >> answer;
                switch (answer) {
                    case 'A': {
                        print_planes('A');
                        break;
                    }
                    case 'B': {
                        print_planes('B');
                        break;
                    }
                    case 'C': {
                        print_planes('C');
                        break;
                    }
                    default:
                        cout << "The option you entered is invalid." << endl;
                }
                break;
            }
            case '3': {
                string country;
                cout << "Wish country do you want to see the airports we operate. " << endl;
                cout << "Enter specific country or enter 'x' to see all airplanes we operate in: ";
                cin >> country;
                print_airports(country);
                break;
            }
            case '4':{
                string destination,origin;
                cout<<"What's the origin : ";
                origin = read_string();
                cout<<"What's the destination : ";
                destination = read_string();
                print_specific_flights(origin,destination);
            }
            case '5':
                continue;
            default: {
                cout << "Invalid option" << endl;
            }
        }
    }

}

void Airline::update_airplane(Airplane & airplane){
    char option;
    while (!cin.eof() and option != '6') {
        cout << endl;
        cout << "1. Add flights" << endl;
        cout << "2. Start a flight or cancel flights" << endl;
        cout << "3. Update flight" << endl;
        cout << "4. Add Service" << endl;
        cout << "5. Remove Service" << endl;
        cout << "6. Exit to the previous menu" << endl;
        option=readChar();
        switch (option) {
            case '1': {
                if (add_flights(airplane))
                    cout << "Added flights successfully" << endl;
                else
                    cout << "You can't add those flights (check if they make sense)" << endl;
                break;
            }
            case '2': {
                char decision;
                cout<<"X to start or Y to cancel";
                decision = readChar();
                if(decision=='Y'){
                    int flights_to_cancel;
                    vector<unsigned > numbers;
                    cout<<"How many flights do you wish to cancel: ";
                    flights_to_cancel = read_int();
                    for(int i = 0; i<flights_to_cancel;i++) {
                        unsigned flight_number;
                        cout << "Enter flight number: ";
                        flight_number = readUnsigned();
                        numbers.push_back(flight_number);
                    }
                    if (airplane.cancel_flights(numbers))
                        cout << "Removed flights successfuly" << endl;
                    else
                        cout << "Error canceling flights (they don't exist or other flights depend on them)" << endl;
                }
                else if(decision=='X'){
                    airplane.start_flight();
                }
                else{
                    cout << "Invalid answer." << endl;
                }
                break;
            }
            case '3': {
                int flight_number;
                cout << "Enter flight number: ";
                flight_number = read_int();
                Flight *f = airplane.find_flight(flight_number);
                if (f != nullptr) {
                    update_flight(*f);
                } else {
                    cout << "No such plane with flight number " << flight_number << endl;
                }
                break;
            }
            case '4': {
                string employee, type;
                cout << "Enter the name of the employee: ";
                if(cin.peek()=='\n')
                    cin.ignore(1); // ignores the '\n'
                getline(cin, employee);
                cout << "Enter the type of service (maintenance or cleaning): ";
                cin >> type;
                cout << "Enter date of the service (day/month/year): ";
                Date d = read_date();
                cout << "Enter hour of the service (hour:minute): ";
                Time t = read_time();
                Schedule schedule(t, d);
                if (type == "maintenance") {
                    Service service = Service(maintenance, schedule, employee);
                    if(!airplane.add_service(service))
                        cout << "Flight scheduled at that time." << endl;
                } else if (type == "cleaning") {
                    Service service = Service(cleaning, schedule, employee);
                    if(!airplane.add_service(service))
                        cout << "Flight scheduled at that time." << endl;
                } else {
                    cout << "The type of service that you entered does not exist." << endl;
                }
                break;
            }
            case '5': {
                if (airplane.remove_service())cout << "Service removed successfully" << endl;
                else cout << "There are no services to remove!" << endl;
                break;
            }
            case '6':
                continue;

            default:
                cout << "The option you entered is invalid." << endl;
        }
    }
}

void Airline::update_flight(Flight & flight){
    char option;
    while (!cin.eof() and option != '3'){
        cout << endl;
        cout << "1. Add passenger" << endl;
        cout << "2. Add a group of passengers" << endl;
        cout << "3. Exit to the previous menu"<<endl;
        option=readChar();
        switch (option) {
            case '1': {
                string passenger_name;
                char answer;
                cout << "Enter the name of the passenger: ";
                if (cin.peek() == '\n')
                    cin.ignore(1);
                getline(cin, passenger_name);
                while(answer!='Y' and answer!='N') {
                    cout << "Does have have luggagge?(Y/N): ";
                    answer = readChar();
                    if (answer == 'Y')
                        flight.add_passenger(Passenger(passenger_name, true));
                    else if (answer == 'N')
                        flight.add_passenger(Passenger(passenger_name, false));
                    else
                        cout << "Invalid answer" << endl;
                }
                break;
            }
            case '2':{
                int number_of_passengers;
                cout << "How many people are in the group?: ";
                number_of_passengers = read_int();
                if(number_of_passengers+flight.get_passengers().size()>flight.get_capacity())
                    cout << "Sorry, there are only " << flight.get_capacity()-flight.get_passengers().size() << " seats available." << endl;
                else{
                    for(unsigned int i=1;i<=number_of_passengers;i++){
                        string passenger_name;
                        char answer;
                        cout << "Enter the name of the passenger: ";
                        if (cin.peek() == '\n')
                            cin.ignore(1);
                        getline(cin, passenger_name);
                        cout << "Does have have luggagge?(Y/N): ";
                        cin >> answer;
                        if (answer == 'Y')
                            flight.add_passenger(Passenger(passenger_name, true));
                        else if (answer == 'N')
                            flight.add_passenger(Passenger(passenger_name, false));
                        else {
                            cout << "Invalid answer, please add the previous passenger again." << endl;
                            i--;
                        }
                    }
                    break;
                }
            }
            case '3':
                continue;
            default:
                cout << "Invalid option" << endl;
        }
    }
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
    Airport airport_lisbon (Airport("Lisbon","Portugal"));
    Airport airport_madrid(Airport("Madrid","Spain"));
    Airport airport_frankfurt(Airport("Frankfurt","Germany"));
    Airport airport_amsterdan(Airport("Amsterdan","Netherlands"));
    Airport airport_newyork(Airport("NewYork","USA"));


    airport_porto.add_transport(LocalTransport("Campanha",15,"Train",train_schedules));
    airport_porto.add_transport(LocalTransport("Porto Sao Bento",12.5,"Train",train_schedules));
    airport_porto.add_transport(LocalTransport("Campanha",15.2,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Aeroport",0.5,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Senhora da Hora",0.5,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Trindade",12,"Subway",subway_schedules));
    airport_porto.add_transport(LocalTransport("Barreiro",0.5,"Bus",bus_schedules));
    airport_porto.add_transport(LocalTransport("Campo 24 de Agosto",13,"Bus",bus_schedules));

    airport_lisbon.add_transport(LocalTransport("Estacao do Oriente",2.4,"Train",train_schedules));
    airport_lisbon.add_transport(LocalTransport("Sete Rios",5,"Train",train_schedules));
    airport_lisbon.add_transport(LocalTransport("Campo Grande",4,"Subway",subway_schedules));
    airport_lisbon.add_transport(LocalTransport("Marques de Pombal",6,"Subway",subway_schedules));
    airport_lisbon.add_transport(LocalTransport("Baixa-Chiado",7,"Subway",subway_schedules));
    airport_lisbon.add_transport(LocalTransport("Oriente",2.5,"Bus",bus_schedules));
    airport_lisbon.add_transport(LocalTransport("Sete Rios",5.3,"Bus",bus_schedules));

    airport_madrid.add_transport(LocalTransport("Atocha",13.5,"Train",train_schedules));
    airport_madrid.add_transport(LocalTransport("Chamartin",12,"Train",train_schedules));
    airport_madrid.add_transport(LocalTransport("Gran Via",13,"Subway",subway_schedules));
    airport_madrid.add_transport(LocalTransport("Concha Espina",10,"Subway",subway_schedules));
    airport_madrid.add_transport(LocalTransport("Alonso Martinez",12.5,"Subway",subway_schedules));
    airport_madrid.add_transport(LocalTransport("Plaza Chamberi",12.3,"Bus",bus_schedules));
    airport_madrid.add_transport(LocalTransport("Estacion de Autobuses de Madrid Estacion Sur",14,"Bus",bus_schedules));

    airport_frankfurt.add_transport(LocalTransport("Hauptbahnhof",11,"Train",train_schedules));
    airport_frankfurt.add_transport(LocalTransport("Frankfurt Airport Long distance rail station",0,"Train",train_schedules));
    airport_frankfurt.add_transport(LocalTransport("Hauptbahnhof",11.3,"Subway",subway_schedules));
    airport_frankfurt.add_transport(LocalTransport("Hauptwache",12,"Subway",subway_schedules));
    airport_frankfurt.add_transport(LocalTransport("Schafflestrabe",16,"Subway",subway_schedules));
    airport_frankfurt.add_transport(LocalTransport("Frankfurt Central Station",10.5,"Bus",bus_schedules));
    airport_frankfurt.add_transport(LocalTransport("Frankfurt Airport Bus Terminal",0.5,"Bus",bus_schedules));

    airport_amsterdan.add_transport(LocalTransport("Centraal",16,"Train",train_schedules));
    airport_amsterdan.add_transport(LocalTransport("Schiphol Airport",0,"Train",train_schedules));
    airport_amsterdan.add_transport(LocalTransport("Zuid",13,"Subway",subway_schedules));
    airport_amsterdan.add_transport(LocalTransport("Nieuwmarkt",15.6,"Subway",subway_schedules));
    airport_amsterdan.add_transport(LocalTransport("Vijzelgracht",14.2,"Subway",subway_schedules));
    airport_amsterdan.add_transport(LocalTransport("Amstelveen",11,"Bus",bus_schedules));
    airport_amsterdan.add_transport(LocalTransport("Sloterdijk",13.5,"Bus",bus_schedules));

    airport_newyork.add_transport(LocalTransport("JFK Airport",0,"Train",train_schedules));
    airport_newyork.add_transport(LocalTransport("Jamaica Station",7.2,"Train",train_schedules));
    airport_newyork.add_transport(LocalTransport("Far Rockaway",12,"Subway",subway_schedules));
    airport_newyork.add_transport(LocalTransport("Times Square",20,"Subway",subway_schedules));
    airport_newyork.add_transport(LocalTransport("Grand Central",25,"Subway",subway_schedules));
    airport_newyork.add_transport(LocalTransport("The Port Authority Midtown Bus Terminal",30,"Bus",bus_schedules));
    airport_newyork.add_transport(LocalTransport("Campo 24 de Agosto",35,"Bus",bus_schedules));


    add_airport(airport_porto);
    add_airport(airport_lisbon);
    add_airport(airport_madrid);
    add_airport(airport_frankfurt);
    add_airport(airport_amsterdan);
    add_airport(airport_newyork);

}

Airplane* Airline::find_airplane(const string& license_plate){
    int low = 0;
    int high = airplanes.size()-1;
    while(low<=high){
        int middle = (low+high)/2;
        if (airplanes[middle].get_license_plate()<license_plate)
            low=middle+1;
        else if(license_plate<airplanes[middle].get_license_plate())
            high=middle-1;
        else{
            return &airplanes[middle];
        }
    }
    return nullptr;
}

bool Airline::add_flights(Airplane & airplane){
    unsigned n_of_flights = (unsigned)-1;
    while(n_of_flights==(unsigned)-1) {
        cout << "How many flights do you want to add: ";
        n_of_flights = readUnsigned();
    }
    vector<Flight> flights_to_add;
    for(unsigned i=0;i<n_of_flights;i++) {
        string origin, destination;
        int flight_number=-1;
        unsigned capacity = airplane.get_capacity();
        while(flight_number==-1) {
            cout << "Enter flight number: ";
            flight_number = read_int();
        }
        Date d;
        while(!(d<Date(0,0,0) or Date(0,0,0)<d)) {
            cout << "Enter date of the flight (day/month/year): ";
            d = read_date();
        }
        Time origin_time;
        while(!(origin_time<Time(0,0) or Time(0,0)<origin_time)) {
            cout << "Enter hour of the flight (hour:minute): ";
            origin_time = read_time();
        }
        Schedule schedule = Schedule(origin_time, d);
        Time duration;
        while(!(duration<Time(0,0) or Time(0,0)<duration)) {
            cout << "Enter the duration of the flight (hour:minute): ";
            duration = read_time();
        }
        while (origin.empty() or find_airport(origin)==nullptr) {
            cout << "Enter origin location: ";
            origin = read_string();
        }
        while (destination.empty() or find_airport(destination) == nullptr) {
            cout << "Enter destination location: ";
            destination = read_string();
        }
        flights_to_add.push_back(Flight(capacity, flight_number, duration, schedule, origin, destination));
    }
    return (airplane.add_flights(flights_to_add));
}

bool Airline::add_airport(const Airport &airport) {
    auto iter = airports.begin();
    for(iter;iter!=airports.end();iter++){
        if(iter->get_name()>airport.get_name())
            break;
        else if(iter->get_name()==airport.get_name())
            return false;
    }
    airports.insert(iter,airport);
    return true;
}

void Airline::check_new_transports(const Airport &airport) {
    char option;
    while(!cin.eof() and option!='3') {
        cout << "Please enter an option" << endl;
        cout << "1. See closest transports" << endl;
        cout << "2. See information about a local transport" << endl;
        cout << "3. Exit to the previous menu" << endl;
        cin >> option;
        switch (option) {
            case '1': {
                print_closest_transports(airport);
                break;
            }
            case '2': {
                string type, name;
                cout << "Enter the type of transport (Subway/Train/Bus): ";
                cin >> type;
                cout << "Enter the name of the transport: ";
                if(cin.peek()=='\n')
                    cin.ignore(1);
                getline(cin,name);
                const LocalTransport *ltptr = airport.find_transport(name, type);
                if (ltptr != nullptr)
                    see_information_transport(*ltptr);
                else
                    cout << "No such transport. " << endl;
                break;
            }
            case '3':
                continue;
            default: {
                cout << "The option you entered is invalid." << endl;
                break;
            }
        }
    }
}

void Airline::see_information_transport(const LocalTransport &l){
    string n;
    Time current_time;
    cout << "Please enter the current time (hh:mm): ";
    current_time = read_time();
    cout << "How many schedules do you want to see? (type x for all): ";
    cin >> n;
    vector<Time> next_schedules;
    if(n=="x"){
        next_schedules = l.next_schedules(l.get_schedules().size(),current_time);
    }
    else{
        if(stoi(n)>l.get_schedules().size()){
            cout << "There aren't that many schedules." << endl ;
        }
        next_schedules = l.next_schedules(stoi(n),current_time);
    }
    bool next_day_print=false;
    for(Time t:next_schedules){
        if(t<current_time and !next_day_print){
            cout << "Next day" << endl;
            next_day_print=true;
        }
        cout << t << endl;
    }
}

Airport * Airline::find_airport(const string &name){
    int low = 0;
    int high = airports.size()-1;
    while(low<=high){
        int middle = (low+high)/2;
        if (airports[middle].get_name()<name)
            low=middle+1;
        else if(name<airports[middle].get_name())
            high=middle-1;
        else{
            return &airports[middle];
        }
    }
    return nullptr;
}


void Airline::print_closest_transports(const Airport &airport){
    int n;
    cout << "How many transports do you wish to see: ";
    n = read_int();
    vector<LocalTransport> nearest_t = airport.get_closest_transports(n);
    if (nearest_t.size() < n) {
        cout << "There are only " << nearest_t.size() << " transports that are near the airport." << endl;
    }
    for (auto &transport: nearest_t) {
        cout << transport.get_name() << "("<<transport.get_type()<< ") : " << transport.get_distance() << " km away." << endl;
    }
}


bool my_sortf1(Airplane const &a1, Airplane const &a2){
    return a1.get_type()<a2.get_type();
}

bool my_sortf2(Airplane const &a1, Airplane const &a2){
    return a1.get_capacity()<a2.get_capacity();
}

void Airline::print_planes(char c) {
    cout<<"Here are the airplanes sorted by your criteria"<<endl;
    vector<Airplane> aux = airplanes;
    if(c=='A'){
        int i=1;
        for(const auto& a:aux){
            cout<<i<< "-"<< a.get_license_plate() << "-"<<a.get_type()<<"-"<<a.get_capacity()<<endl;
            i++;
        }
    }
    else if(c=='B'){
        sort(aux.begin(),aux.end(),my_sortf1);
        int i=1;
        for(const auto& a:aux){
            cout<<i<< "-"<< a.get_license_plate() << "-"<<a.get_type()<<"-"<<a.get_capacity()<<endl;
            i++;
        }
    }
    else{
        sort(aux.begin(),aux.end(),my_sortf2);
        int i=1;
        for(const auto& a:aux){
            cout<<i<< "-"<< a.get_license_plate() << "-"<<a.get_type()<<"-"<<a.get_capacity()<<endl;
            i++;
        }
    }
}

void Airline::print_airports(string country) {
    if(country != "x"){
        cout << "We have the following airport(s) operating in "<<country<<" :"<<endl;
        for(Airport &a: airports){
            if(a.get_country() == country){
                cout<< a.get_name()<<endl;
            }
        }
    }
    else{
        cout << "We have the following airports that are operational at the moment:"<<endl;
        for(Airport &a: airports){
            cout<< a.get_name()<<endl;
        }
    }
}

bool rule_flight(Flight const &f1,Flight const &f2 ){
    return f1.get_schedule()<f2.get_schedule();
}

void Airline::print_soonest_flights(int n){
    vector<Flight> all_flights;
    for(Airplane const &a:airplanes){
        for(Flight const  &f : a.get_flights()){
            all_flights.push_back(f);
        }
    }
    sort(all_flights.begin(), all_flights.end(), rule_flight);
    if(n>all_flights.size()){
        cout << "We don't have that many flights."<<endl;
        cout<< "Here are all the flights we have sorted by schedule"<<endl;
        for(auto const &flight: all_flights){
            cout<<"Flight number "<< flight.get_number()<<":"<<endl;
            cout<<"Scheduled at: "<< flight.get_schedule()<<endl;
            cout<<"Flight duration of "<< flight.get_duration()<<endl;
            cout<<"With origin in " << flight.get_origin()<< " and destination "<< flight.get_destination()<<endl << endl;
        }
    }
    else{
        cout << "Here are the next "<< n << " flights:"<<endl;
        for(int i = 0;i<n;i++){
            cout<<"Flight number "<< all_flights[i].get_number()<<":"<<endl;
            cout<<"Scheduled at: "<< all_flights[i].get_schedule()<<endl;
            cout<<"Flight duration of "<< all_flights[i].get_duration()<<endl;
            cout<<"With origin in " << all_flights[i].get_origin()<< " and destination "<< all_flights[i].get_destination()<<endl;
        }
    }
}

void Airline::print_specific_flights(const string &origin,const string& destination) {
    vector<Flight> answer;
    for(Airplane const &a:airplanes){
        for(Flight const  &f : a.get_flights()){
            if(f.get_destination()== destination and f.get_origin()==origin)
                answer.push_back(f);
        }
    }
    sort(answer.begin(),answer.end(), rule_flight);
    for(auto const &flight: answer){
        if(flight.get_destination()== destination and flight.get_origin()==origin){
            cout<<"Flight number "<< flight.get_number()<<":"<<endl;
            cout<<"Scheduled at: "<< flight.get_schedule()<<endl;
            cout<<"Flight duration of "<< flight.get_duration()<<endl;
        }
    }
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
}

