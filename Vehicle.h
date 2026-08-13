#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "Enums.h"

class vehicle {
public:
    vehicletype type;
    std::string reg_number;

    vehicle(vehicletype vtype, std::string reg_num)
        : type(vtype), reg_number(reg_num) {}
};

#endif
