//
// Created by pedro on 01/12/21.
//

#include "Service.h"

Time Service::get_duration() const {
    if(this->type_service == cleaning) return CLEANING_DURATION;
    else return MAINTENANCE_DURATION;
}
