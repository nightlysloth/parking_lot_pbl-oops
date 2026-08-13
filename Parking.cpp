#include "Parking.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

parking::parking(string societyname, string towername, int carcap, int bikecap, int truckcap)
    : Society(societyname), tower(towername), capforCars(carcap), capforBikes(bikecap), capforTrucks(truckcap) {

    for (int i = 1; i <= capforCars; i++)
        carslots.push_back(ParkingSlot(i, vehicletype::car));

    for (int i = 1; i <= capforBikes; i++)
        bikeslots.push_back(ParkingSlot(i, vehicletype::bike));

    for (int i = 1; i <= capforTrucks; i++)
        truckslots.push_back(ParkingSlot(i, vehicletype::truck));
}

parking::~parking() {
    for (auto v : vehicles) delete v;
    for (auto t : tickets) delete t;
}

vehicle* parking::findVehicle(string regNumber) {
    for (auto v : vehicles) {
        if (v->reg_number == regNumber) return v;
    }
    return nullptr;
}

Ticket* parking::findTicket(int ticketNumber) {
    for (auto t : tickets) {
        if (t->ticketNumber == ticketNumber) return t;
    }
    return nullptr;
}

vector<ParkingSlot>* parking::getSlots(vehicletype type) {
    if (type == vehicletype::car) return &carslots;
    if (type == vehicletype::bike) return &bikeslots;
    return &truckslots;
}

Ticket* parking::park(vehicle* v, int ticketid) {
    vector<ParkingSlot>* slots = getSlots(v->type);

    for (auto& slot : *slots) {
        if (slot.status == slotstatus::vacant) {
            slot.status = slotstatus::reserved;
            Ticket* ticket = new Ticket(ticketid, v, &slot);
            tickets.push_back(ticket);
            vehicles.push_back(v);

            cout << "\nVehicle parked successfully!\n";
            cout << "Vehicle Number : " << v->reg_number << endl;
            cout << "Vehicle Type   : " << vehicleTypeToString(v->type) << endl;
            cout << "Slot Number    : " << slot.slotNumber << endl;
            cout << "Ticket Number  : " << ticket->ticketNumber << endl;

            return ticket;
        }
    }

    cout << "\nNo parking slot available for " << vehicleTypeToString(v->type) << ".\n";
    return nullptr;
}

int parking::calculateCharges(Ticket* t) {
    auto duration = chrono::duration_cast<chrono::minutes>(t->exitTime - t->inTime).count();
    long long hours = (duration + 59) / 60;
    if (hours < 1) hours = 1;

    int rate;
    switch (t->Vehicle->type) {
        case vehicletype::bike:  rate = 10; break;
        case vehicletype::car:   rate = 30; break;
        case vehicletype::truck: rate = 50; break;
    }

    return hours * rate;
}

void parking::unpark(int ticketNumber) {
    Ticket* t = findTicket(ticketNumber);

    if (t == nullptr) {
        cout << "\nInvalid ticket number.\n";
        return;
    }

    if (t->status == ticketstatus::done) {
        cout << "\nThis ticket is already closed.\n";
        return;
    }

    t->exitTime = chrono::system_clock::now();
    t->charges = calculateCharges(t);
    t->status = ticketstatus::done;
    t->slot->status = slotstatus::vacant;

    auto duration = chrono::duration_cast<chrono::minutes>(t->exitTime - t->inTime).count();
    long long hours = (duration + 59) / 60;
    if (hours < 1) hours = 1;

    cout << "\n====================================\n";
    cout << "           PARKING BILL\n";
    cout << "====================================\n";
    cout << "Ticket Number : " << t->ticketNumber << endl;
    cout << "Vehicle Number: " << t->Vehicle->reg_number << endl;
    cout << "Vehicle Type  : " << vehicleTypeToString(t->Vehicle->type) << endl;
    cout << "Slot Number   : " << t->slot->slotNumber << endl;
    cout << "Duration      : " << duration << " minutes\n";
    cout << "Charged Hours : " << hours << endl;
    cout << "Total Charges : ₹" << t->charges << endl;
    cout << "====================================\n";
    cout << "Vehicle exited successfully.\n";
}

void parking::displaySlots(vector<ParkingSlot>& slots) {
    for (auto& slot : slots) {
        cout << "Slot " << setw(3) << slot.slotNumber << " : " << slotStatusToString(slot.status) << endl;
    }
}

void parking::displayAllSlots() {
    cout << "\n====================================\n";
    cout << "          PARKING SLOT STATUS\n";
    cout << "====================================\n";
    cout << "\n--- CAR SLOTS ---\n";
    displaySlots(carslots);
    cout << "\n--- BIKE SLOTS ---\n";
    displaySlots(bikeslots);
    cout << "\n--- TRUCK SLOTS ---\n";
    displaySlots(truckslots);
}

void parking::displayActiveTickets() {
    bool found = false;
    cout << "\n====================================\n";
    cout << "          ACTIVE TICKETS\n";
    cout << "====================================\n";

    for (auto t : tickets) {
        if (t->status == ticketstatus::active) {
            found = true;
            cout << "\nTicket Number : " << t->ticketNumber;
            cout << "\nVehicle Number: " << t->Vehicle->reg_number;
            cout << "\nVehicle Type  : " << vehicleTypeToString(t->Vehicle->type);
            cout << "\nSlot Number   : " << t->slot->slotNumber;
            cout << "\nStatus        : Active\n";
        }
    }

    if (!found) cout << "\nNo active tickets.\n";
}

void parking::displayTicketHistory() {
    if (tickets.empty()) {
        cout << "\nNo ticket history available.\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "           TICKET HISTORY\n";
    cout << "====================================\n";

    for (auto t : tickets) {
        cout << "\nTicket Number : " << t->ticketNumber;
        cout << "\nVehicle Number: " << t->Vehicle->reg_number;
        cout << "\nVehicle Type  : " << vehicleTypeToString(t->Vehicle->type);
        cout << "\nSlot Number   : " << t->slot->slotNumber;
        cout << "\nStatus        : " << ticketStatusToString(t->status);
        if (t->status == ticketstatus::done) {
            cout << "\nCharges       : ₹" << t->charges;
        }
        cout << "\n";
    }
}

void parking::displayParkingInfo() {
    cout << "\n====================================\n";
    cout << "        PARKING INFORMATION\n";
    cout << "====================================\n";
    cout << "Society : " << Society << endl;
    cout << "Tower   : " << tower << endl;
    cout << "\nCapacity:\n";
    cout << "Cars    : " << capforCars << endl;
    cout << "Bikes   : " << capforBikes << endl;
    cout << "Trucks  : " << capforTrucks << endl;
}
