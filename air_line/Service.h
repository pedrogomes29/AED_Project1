//
// Created by pedro on 01/12/21.
//
#ifndef AIRLINE_SERVICE_H
#define AIRLINE_SERVICE_H

#include <string>


using namespace std;

enum Type{maintenance,cleaning};


class Service {
private:
    Type type_service;
    string date;
    string name_of_employee;
};


#endif //AIRLINE_SERVICE_H
