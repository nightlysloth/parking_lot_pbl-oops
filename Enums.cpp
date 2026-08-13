#include "Enums.h"

std::string vehicleTypeToString(vehicletype type) {
    switch (type) {
        case vehicletype::car:   return "Car";
        case vehicletype::bike:  return "Bike";
        case vehicletype::truck: return "Truck";
    }
    return "Unknown";
}

std::string slotStatusToString(slotstatus status) {
    return (status == slotstatus::vacant) ? "Vacant" : "Occupied";
}

std::string ticketStatusToString(ticketstatus status) {
    return (status == ticketstatus::active) ? "Active" : "Done";
}
