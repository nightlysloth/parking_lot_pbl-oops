#include <iostream>
#include <string>
#include "Parking.h"

using namespace std;

vehicletype getVehicleType() {
    int choice;
    while (true) {
        cout << "\nSelect Vehicle Type:\n";
        cout << "1. Car\n2. Bike\n3. Truck\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) return vehicletype::car;
        if (choice == 2) return vehicletype::bike;
        if (choice == 3) return vehicletype::truck;

        cout << "\nInvalid choice. Try again.\n";
    }
}

int main() {
    parking Parking("ABC Residency", "Tower A", 5, 10, 3);

    int ticketCounter = 1001;
    int choice;

    do {
        cout << "\n\n====================================\n";
        cout << "       PARKING MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Exit Vehicle\n";
        cout << "3. Display Parking Slots\n";
        cout << "4. Display Active Tickets\n";
        cout << "5. Display Ticket History\n";
        cout << "6. Parking Information\n";
        cout << "7. Exit Program\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string regNumber;
            cout << "\nEnter vehicle registration number: ";
            cin >> regNumber;

            vehicle* existing = Parking.findVehicle(regNumber);
            bool alreadyParked = false;

            if (existing != nullptr) {
                for (auto t : Parking.tickets) {
                    if (t->Vehicle == existing && t->status == ticketstatus::active) {
                        alreadyParked = true;
                        break;
                    }
                }
            }

            if (alreadyParked) {
                cout << "\nThis vehicle is already parked.\n";
                continue;
            }

            vehicletype type = getVehicleType();
            vehicle* v = new vehicle(type, regNumber);

            Ticket* ticket = Parking.park(v, ticketCounter);
            if (ticket != nullptr) {
                ticketCounter++;
            } else {
                delete v;
            }
        }
        else if (choice == 2) {
            int ticketNumber;
            cout << "\nEnter ticket number: ";
            cin >> ticketNumber;
            Parking.unpark(ticketNumber);
        }
        else if (choice == 3) {
            Parking.displayAllSlots();
        }
        else if (choice == 4) {
            Parking.displayActiveTickets();
        }
        else if (choice == 5) {
            Parking.displayTicketHistory();
        }
        else if (choice == 6) {
            Parking.displayParkingInfo();
        }
        else if (choice == 7) {
            cout << "\nThank you for using the Parking Management System.\n";
        }
        else {
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
