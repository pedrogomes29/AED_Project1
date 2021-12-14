//
// Created by Pedro on 14/12/2021.
//

#include "Airport.h"

Airport::Airport(string name):name(name),transports(LocalTransport("",0.0,vector<Schedule>())) {

}