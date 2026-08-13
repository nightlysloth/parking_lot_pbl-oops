#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Enums.h"

class ParkingSlot {
public:
    int slotNumber;
    vehicletype type;
    slotstatus status;

    ParkingSlot(int num, vehicletype t)
        : slotNumber(num), type(t), status(slotstatus::vacant) {}
};

#endif
