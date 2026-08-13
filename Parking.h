#ifndef PARKING_H
#define PARKING_H

#include <string>
#include <vector>
#include "Enums.h"
#include "Vehicle.h"
#include "ParkingSlot.h"
#include "Ticket.h"

class parking {
public:
    std::string Society;
    std::string tower;

    int capforCars;
    int capforBikes;
    int capforTrucks;

    std::vector<ParkingSlot> carslots;
    std::vector<ParkingSlot> bikeslots;
    std::vector<ParkingSlot> truckslots;

    std::vector<vehicle*> vehicles;
    std::vector<Ticket*> tickets;

    parking(std::string societyname, std::string towername, int carcap, int bikecap, int truckcap);
    ~parking();

    vehicle* findVehicle(std::string regNumber);
    Ticket* findTicket(int ticketNumber);
    std::vector<ParkingSlot>* getSlots(vehicletype type);

    Ticket* park(vehicle* v, int ticketid);
    int calculateCharges(Ticket* t);
    void unpark(int ticketNumber);

    void displaySlots(std::vector<ParkingSlot>& slots);
    void displayAllSlots();
    void displayActiveTickets();
    void displayTicketHistory();
    void displayParkingInfo();
};

#endif
