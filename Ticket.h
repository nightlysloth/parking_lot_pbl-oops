#ifndef TICKET_H
#define TICKET_H

#include <chrono>
#include "Enums.h"
#include "Vehicle.h"
#include "ParkingSlot.h"

class Ticket {
public:
    int ticketNumber;
    vehicle* Vehicle;
    ParkingSlot* slot;
    int charges;
    ticketstatus status;

    std::chrono::system_clock::time_point inTime;
    std::chrono::system_clock::time_point exitTime;

    Ticket(int num, vehicle* v, ParkingSlot* s)
        : ticketNumber(num), Vehicle(v), slot(s), charges(0), status(ticketstatus::active) {
        inTime = std::chrono::system_clock::now();
    }
};

#endif
