# Parking Management System

## 1. Project Overview

The **Parking Management System** is a console-based C++ application designed to manage vehicle parking in a residential society, commercial complex, or similar parking facility.

The system automates the core parking workflow:

1. Register a vehicle at entry.
2. Assign an appropriate vacant parking slot.
3. Generate a unique parking ticket.
4. Track the vehicle while it is parked.
5. Process vehicle exit.
6. Calculate parking charges based on duration and vehicle type.
7. Release the occupied parking slot.
8. Maintain ticket history and parking status.

The project is implemented using **Object-Oriented Programming (OOP)** concepts in C++ and uses STL containers and `std::chrono` for time management.

---

## 2. Objectives

The primary objectives are:

- Automate parking-slot allocation.
- Maintain separate slots for cars, bikes, and trucks.
- Generate unique tickets for parked vehicles.
- Track entry and exit times.
- Calculate parking fees automatically.
- Prevent multiple active parking tickets for the same vehicle.
- Track vacant and occupied slots.
- Maintain active-ticket and historical-ticket information.
- Provide a simple menu-driven console interface.
- Demonstrate practical usage of C++ OOP concepts.

---

## 3. Scope

### In Scope

The first version of the system will support:

- Society and tower information.
- Multiple vehicle types.
- Vehicle registration numbers.
- Vehicle-specific parking slots.
- Automatic slot assignment.
- Parking tickets.
- Entry-time tracking.
- Exit-time tracking.
- Hour-based parking charges.
- Active ticket management.
- Completed ticket history.
- Parking-slot status.
- Basic parking statistics.
- Console-based interaction.
- Dynamic object management.

### Out of Scope

The initial version will not include:

- Graphical user interface.
- Web interface.
- Mobile application.
- Online payments.
- Database server.
- Cloud synchronization.
- RFID integration.
- Number-plate recognition.
- Real-time sensors.
- User authentication.
- Multi-location parking management.

These can be considered future extensions.

---

# 4. Target Users

## 4.1 Parking Operator

The parking operator can:

- Park vehicles.
- Generate tickets.
- Process vehicle exits.
- Check available slots.
- View active tickets.
- View parking history.

## 4.2 Society/Facility Administrator

An administrator can use the system to:

- Configure parking capacity.
- Monitor occupancy.
- Review ticket history.
- Analyze parking usage.
- Configure parking rates in future versions.

## 4.3 Vehicle Owner

The vehicle owner indirectly interacts with the system by:

- Providing vehicle registration information.
- Receiving a ticket number.
- Using the ticket number when leaving the parking facility.

---

# 5. Functional Requirements

## FR-01: Parking Facility Configuration

The system shall allow a parking facility to be initialized with:

- Society name.
- Tower/building name.
- Number of car slots.
- Number of bike slots.
- Number of truck slots.

Example:

```text
Society: ABC Residency
Tower: Tower A

Car Slots: 50
Bike Slots: 100
Truck Slots: 10
```

---

## FR-02: Vehicle Registration

The system shall allow the operator to enter:

- Vehicle registration number.
- Vehicle type.

Supported vehicle types:

```text
1. Car
2. Bike
3. Truck
```

Example:

```text
Registration Number: UP15AB1234
Vehicle Type: Car
```

---

## FR-03: Automatic Slot Allocation

The system shall automatically locate the first available slot matching the vehicle type.

For example:

```text
Car Slots

Slot 1 → Occupied
Slot 2 → Occupied
Slot 3 → Vacant
Slot 4 → Vacant
```

A new car shall automatically receive:

```text
Slot 3
```

The user should not need to manually select a slot.

---

## FR-04: Vehicle-Type Restrictions

A vehicle shall only be assigned to an appropriate slot.

For example:

```text
Car → Car Slot
Bike → Bike Slot
Truck → Truck Slot
```

A bike shall not be automatically assigned to a car slot.

---

## FR-05: Ticket Generation

Every successful parking operation shall generate a unique ticket number.

Example:

```text
Ticket Number: 1001
```

The ticket shall contain:

- Ticket number.
- Vehicle.
- Registration number.
- Vehicle type.
- Assigned parking slot.
- Entry timestamp.
- Current ticket status.

---

## FR-06: Entry Time Tracking

The system shall record the exact time at which the vehicle is parked.

The implementation shall use:

```cpp
std::chrono::system_clock
```

The entry timestamp shall be stored in the ticket.

---

## FR-07: Active Ticket Management

A ticket shall initially have:

```text
Status = Active
```

An active ticket represents a vehicle currently inside the parking facility.

The system shall allow active tickets to be displayed.

---

## FR-08: Duplicate Active Vehicle Prevention

The system shall prevent a vehicle from being parked multiple times simultaneously.

For example:

```text
UP15AB1234 → Active Ticket 1001
```

Attempting to park:

```text
UP15AB1234
```

again shall produce an error:

```text
This vehicle is already parked.
```

Once the existing ticket is completed, the vehicle may be parked again.

---

## FR-09: Parking Exit

The operator shall be able to process vehicle exit using the ticket number.

Example:

```text
Enter Ticket Number: 1001
```

The system shall:

1. Find the ticket.
2. Verify that it exists.
3. Verify that it is active.
4. Record the exit timestamp.
5. Calculate parking duration.
6. Calculate the parking fee.
7. Mark the ticket as completed.
8. Release the parking slot.
9. Display the final bill.

---

## FR-10: Invalid Ticket Handling

If an invalid ticket number is entered, the system shall display:

```text
Invalid ticket number.
```

The system shall not crash or modify parking data.

---

## FR-11: Duplicate Exit Prevention

A completed ticket cannot be used to exit the vehicle again.

Example:

```text
This ticket is already closed.
```

The system shall leave the ticket and parking state unchanged.

---

# 6. Parking Fee Requirements

Parking charges shall depend on:

1. Vehicle type.
2. Parking duration.

Default rates:

| Vehicle Type | Rate |
|---|---:|
| Bike | ₹10/hour |
| Car | ₹30/hour |
| Truck | ₹50/hour |

These rates should ideally be configurable in a future version.

---

## 6.1 Billing Rule

The system shall charge based on started hours.

Formula:

```text
Charged Hours = ceil(Parking Duration in Minutes / 60)
```

Minimum chargeable duration:

```text
1 hour
```

Examples:

| Duration | Charged Hours |
|---:|---:|
| 5 minutes | 1 |
| 30 minutes | 1 |
| 59 minutes | 1 |
| 60 minutes | 1 |
| 61 minutes | 2 |
| 120 minutes | 2 |
| 121 minutes | 3 |

---

## 6.2 Charge Calculation

```text
Total Charge =
Charged Hours × Vehicle Hourly Rate
```

Example:

```text
Vehicle: Car
Duration: 2 hours 15 minutes
Rate: ₹30/hour

Charged Hours = 3

Total = 3 × ₹30
      = ₹90
```

---

# 7. Ticket Lifecycle

A ticket follows the following lifecycle:

```text
              Vehicle Enters
                    |
                    ↓
               Ticket Created
                    |
                    ↓
                  ACTIVE
                    |
                    |
              Vehicle Exits
                    |
                    ↓
             Exit Time Recorded
                    |
                    ↓
              Charges Calculated
                    |
                    ↓
                   DONE
```

Valid state transition:

```text
ACTIVE → DONE
```

Invalid transition:

```text
DONE → ACTIVE
```

---

# 8. Parking Slot Lifecycle

Each parking slot has two possible states:

```text
VACANT
OCCUPIED
```

In the implementation, the occupied state is represented by:

```cpp
slotstatus::reserved
```

Lifecycle:

```text
VACANT
   |
   | Vehicle parked
   ↓
RESERVED
   |
   | Vehicle exits
   ↓
VACANT
```

---

# 9. Data Model

## 9.1 Vehicle

```cpp
class vehicle
```

### Attributes

| Attribute | Type | Description |
|---|---|---|
| `type` | `vehicletype` | Type of vehicle |
| `reg_number` | `string` | Registration number |

---

## 9.2 ParkingSlot

```cpp
class ParkingSlot
```

### Attributes

| Attribute | Type | Description |
|---|---|---|
| `slotNumber` | `int` | Slot identifier |
| `type` | `vehicletype` | Supported vehicle type |
| `status` | `slotstatus` | Vacant/occupied |

---

## 9.3 Ticket

```cpp
class Ticket
```

### Attributes

| Attribute | Type | Description |
|---|---|---|
| `ticketNumber` | `int` | Unique ticket identifier |
| `Vehicle` | `vehicle*` | Associated vehicle |
| `slot` | `ParkingSlot*` | Assigned slot |
| `charges` | `int` | Final parking charge |
| `status` | `ticketstatus` | Active/done |
| `inTime` | `time_point` | Entry timestamp |
| `exitTime` | `time_point` | Exit timestamp |

---

## 9.4 Parking

```cpp
class parking
```

### Attributes

| Attribute | Type | Description |
|---|---|---|
| `Society` | `string` | Society name |
| `tower` | `string` | Tower/building name |
| `capforCars` | `int` | Car capacity |
| `capforBikes` | `int` | Bike capacity |
| `capforTrucks` | `int` | Truck capacity |
| `carslots` | `vector<ParkingSlot>` | Car slots |
| `bikeslots` | `vector<ParkingSlot>` | Bike slots |
| `truckslots` | `vector<ParkingSlot>` | Truck slots |
| `vehicles` | `vector<vehicle*>` | Registered vehicles |
| `tickets` | `vector<Ticket*>` | Ticket records |

---

# 10. Enumerations

## Vehicle Type

```cpp
enum class vehicletype {
    car,
    bike,
    truck
};
```

## Slot Status

```cpp
enum class slotstatus {
    reserved,
    vacant
};
```

## Ticket Status

```cpp
enum class ticketstatus {
    active,
    done
};
```

---

# 11. System Menu

The main menu shall provide:

```text
====================================
       PARKING MANAGEMENT SYSTEM
====================================

1. Park Vehicle
2. Exit Vehicle
3. Display Parking Slots
4. Display Active Tickets
5. Display Ticket History
6. Parking Information
7. Exit Program
```

---

# 12. Menu Operations

## 12.1 Park Vehicle

Input:

```text
Registration Number
Vehicle Type
```

Output:

```text
Vehicle parked successfully!

Vehicle Number : UP15AB1234
Vehicle Type   : Car
Slot Number    : 3
Ticket Number  : 1001
```

---

## 12.2 Exit Vehicle

Input:

```text
Ticket Number
```

Output:

```text
====================================
           PARKING BILL
====================================

Ticket Number : 1001
Vehicle Number: UP15AB1234
Vehicle Type  : Car
Slot Number   : 3
Duration      : 125 minutes
Charged Hours : 3
Total Charges : ₹90

====================================
Vehicle exited successfully.
```

---

## 12.3 Display Parking Slots

Example:

```text
--- CAR SLOTS ---

Slot   1 : Occupied
Slot   2 : Vacant
Slot   3 : Occupied
Slot   4 : Vacant
Slot   5 : Vacant
```

The same information shall be available for bikes and trucks.

---

## 12.4 Display Active Tickets

Example:

```text
====================================
          ACTIVE TICKETS
====================================

Ticket Number : 1001
Vehicle Number: UP15AB1234
Vehicle Type  : Car
Slot Number   : 3
Status        : Active
```

---

## 12.5 Display Ticket History

The system shall display both:

```text
Active
```

and:

```text
Done
```

tickets.

Completed tickets shall additionally show their charges.

---

# 13. Error Handling

The system shall handle the following cases.

### Invalid menu option

```text
Invalid choice. Please try again.
```

### No available slot

```text
No parking slot available for Car.
```

### Duplicate active vehicle

```text
This vehicle is already parked.
```

### Invalid ticket

```text
Invalid ticket number.
```

### Reusing completed ticket

```text
This ticket is already closed.
```

### Empty ticket history

```text
No ticket history available.
```

---

# 14. Object-Oriented Design

The project demonstrates the following OOP concepts.

## Encapsulation

Vehicle, ticket, parking-slot, and parking-facility data are grouped into separate classes.

```text
Vehicle
ParkingSlot
Ticket
Parking
```

---

## Abstraction

The user does not need to know how slot allocation or fee calculation works.

For example:

```cpp
Parking.park(vehicle, ticketID);
```

internally handles:

- Finding slots.
- Checking availability.
- Reserving slots.
- Creating tickets.

---

## Composition / Association

A parking facility manages multiple parking slots and tickets.

Conceptually:

```text
Parking
 ├── Car Slots
 ├── Bike Slots
 ├── Truck Slots
 ├── Vehicles
 └── Tickets
```

A ticket associates:

```text
Vehicle ↔ ParkingSlot
```

---

## Polymorphism

The current version does not require inheritance-based runtime polymorphism because vehicle behavior is primarily differentiated through:

```cpp
enum class vehicletype
```

A future version could introduce:

```text
Vehicle
 ├── Car
 ├── Bike
 └── Truck
```

with polymorphic pricing and vehicle-specific behavior.

---

# 15. Data Structures

## `vector`

Used for storing:

```cpp
vector<ParkingSlot>
vector<vehicle*>
vector<Ticket*>
```

Advantages:

- Dynamic size.
- Simple iteration.
- STL support.
- Efficient sequential access.

---

# 16. Time Management

The application uses:

```cpp
chrono::system_clock
```

Entry:

```cpp
inTime = chrono::system_clock::now();
```

Exit:

```cpp
exitTime = chrono::system_clock::now();
```

Duration:

```cpp
exitTime - inTime
```

The duration is converted into minutes before calculating the final bill.

---

# 17. Memory Management

The current implementation dynamically allocates:

```cpp
new vehicle(...)
new Ticket(...)
```

The `parking` destructor releases these objects:

```cpp
~parking() {
    for (auto v : vehicles)
        delete v;

    for (auto t : tickets)
        delete t;
}
```

This prevents dynamically allocated objects from remaining in memory after the parking-system object is destroyed.

### Future improvement

The project should eventually replace raw owning pointers with:

```cpp
std::unique_ptr
```

to implement RAII-based memory management.

---

# 18. Expected Workflow

A typical session:

```text
START
  |
  ↓
Display Main Menu
  |
  ↓
Park Vehicle
  |
  ├── Enter Registration Number
  |
  ├── Select Vehicle Type
  |
  ├── Find Available Slot
  |
  ├── Reserve Slot
  |
  └── Generate Ticket
  |
  ↓
Vehicle remains parked
  |
  ↓
Display Active Tickets
  |
  ↓
Vehicle Exit
  |
  ├── Enter Ticket Number
  |
  ├── Find Ticket
  |
  ├── Calculate Duration
  |
  ├── Calculate Charges
  |
  ├── Release Slot
  |
  └── Mark Ticket DONE
  |
  ↓
Display Ticket History
  |
  ↓
END
```

---

# 19. Non-Functional Requirements

## Performance

The application should respond immediately for normal parking-lot sizes.

The current implementation uses linear searches, which are sufficient for a small parking facility.

Examples:

```text
Find ticket       → O(n)
Find vehicle      → O(n)
Find vacant slot  → O(n)
```

For very large facilities, hash-based structures could improve lookup performance.

---

## Reliability

The application should:

- Never assign an occupied slot.
- Never assign a slot to an incompatible vehicle type.
- Never close an already completed ticket.
- Never allow duplicate active parking for a vehicle.
- Never charge without a valid active ticket.

---

## Usability

The interface should:

- Be menu-driven.
- Clearly label inputs.
- Clearly display errors.
- Clearly display parking information.
- Clearly display bills.

---

## Maintainability

The system should separate responsibilities between:

```text
Vehicle
ParkingSlot
Ticket
Parking
```

rather than implementing the entire application inside `main()`.

---

# 20. Proposed Project Structure

A future multi-file implementation should use:

```text
ParkingManagementSystem/
│
├── README.md
│
├── include/
│   ├── Vehicle.h
│   ├── ParkingSlot.h
│   ├── Ticket.h
│   └── Parking.h
│
├── src/
│   ├── Vehicle.cpp
│   ├── ParkingSlot.cpp
│   ├── Ticket.cpp
│   ├── Parking.cpp
│   └── main.cpp
│
├── build/
│
└── Makefile
```

For the initial version, a single `main.cpp` file is acceptable.

---

# 21. Compilation

Using `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o parking
```

Run:

```bash
./parking
```

For a stricter debugging build:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -g main.cpp -o parking
```

---

# 22. Testing Requirements

The following scenarios should be tested.

## Test Case 1 — Normal Parking

```text
Vehicle: Car
Registration: UP15AB1234
```

Expected:

```text
Slot assigned
Ticket generated
Status = Active
```

---

## Test Case 2 — Full Parking

Fill every car slot.

Attempt to park another car.

Expected:

```text
No parking slot available for Car.
```

---

## Test Case 3 — Duplicate Vehicle

Park:

```text
UP15AB1234
```

again before exiting.

Expected:

```text
This vehicle is already parked.
```

---

## Test Case 4 — Invalid Ticket

Enter:

```text
9999
```

Expected:

```text
Invalid ticket number.
```

---

## Test Case 5 — Valid Exit

Enter an active ticket number.

Expected:

- Exit time recorded.
- Charges calculated.
- Ticket becomes `DONE`.
- Slot becomes `VACANT`.

---

## Test Case 6 — Duplicate Exit

Attempt to exit using an already completed ticket.

Expected:

```text
This ticket is already closed.
```

---

## Test Case 7 — Different Vehicle Rates

Verify:

```text
Bike  → ₹10/hour
Car   → ₹30/hour
Truck → ₹50/hour
```

---

# 23. Future Enhancements

## Phase 2 — Better Parking Management

Potential additions:

- Parking floors.
- Numbered parking zones.
- Reserved slots.
- Disabled-accessible slots.
- EV charging slots.
- VIP parking.
- Compact-car slots.
- Motorcycle-specific areas.

---

## Phase 3 — Persistent Storage

Currently, all data is lost when the application terminates.

Future versions should store information in:

```text
.txt
.csv
JSON
SQLite
MySQL/PostgreSQL
```

Possible persistent data:

```text
Vehicles
Tickets
Parking Slots
Payment History
Parking Rates
```

---

## Phase 4 — User Accounts

Introduce:

```text
Admin
Parking Operator
Vehicle Owner
```

with role-based permissions.

Example:

```text
Admin
 ├── Configure capacity
 ├── Configure rates
 ├── View reports
 └── Manage operators

Operator
 ├── Park vehicle
 ├── Exit vehicle
 └── View tickets

User
 └── View parking information
```

---

## Phase 5 — Payment System

Add:

- Cash payment.
- UPI.
- Card payment.
- Payment status.
- Transaction ID.
- Digital receipts.

Example:

```text
Parking Charge : ₹90
Payment Method  : UPI
Transaction ID  : TXN123456
Payment Status  : PAID
```

---

## Phase 6 — GUI

Replace the console interface with:

- Qt desktop application.
- Web application.
- Android application.

A graphical dashboard could show:

```text
┌─────────────────────────────────────┐
│       PARKING MANAGEMENT SYSTEM     │
├─────────────────────────────────────┤
│ Cars     : 35 / 50                  │
│ Bikes    : 72 / 100                 │
│ Trucks   :  4 / 10                  │
├─────────────────────────────────────┤
│ Vacant Slots : 49                   │
│ Active Tickets: 111                 │
└─────────────────────────────────────┘
```

---

# 24. Advanced Future Architecture

A production-oriented version could be structured as:

```text
                    Parking Management System
                              |
        ┌─────────────────────┼─────────────────────┐
        ↓                     ↓                     ↓
   Presentation           Business Logic         Storage
        |                     |                     |
 Console / GUI          Parking Manager         Database
                              |
            ┌─────────────────┼─────────────────┐
            ↓                 ↓                 ↓
        Vehicles          Parking Slots       Tickets
            |                 |                 |
            └─────────────────┼─────────────────┘
                              ↓
                           Payment
```

---

# 25. Security Considerations

For a future networked implementation:

- Authentication shall be required for administrators.
- Passwords must never be stored in plaintext.
- Administrative operations should require authorization.
- Payment information must not be stored unnecessarily.
- Database queries should use parameterized statements.
- User input must be validated.
- Logs should not expose sensitive information.

---

# 26. Limitations of Current Version

The current console implementation has several limitations:

1. Data is stored only in RAM.
2. Data disappears when the application closes.
3. There is no authentication.
4. There is no database.
5. There is no payment gateway.
6. Parking rates are hard-coded.
7. The application represents one parking facility.
8. There is no concurrent access.
9. There is no GUI.
10. Raw pointers are used for object ownership.
11. Ticket timestamps are not persisted.
12. There is no automatic receipt file generation.

These are intentional limitations of the initial implementation rather than requirements for the core prototype.

---

# 27. Success Criteria

The project will be considered successful when it can reliably:

- Create a parking facility.
- Create parking slots according to configured capacity.
- Accept vehicle information.
- Assign compatible vacant slots.
- Reject parking when no compatible slot exists.
- Prevent duplicate active parking.
- Generate unique tickets.
- Record entry time.
- Find tickets using ticket numbers.
- Calculate parking duration.
- Calculate vehicle-specific charges.
- Release slots after vehicle exit.
- Maintain active-ticket information.
- Maintain ticket history.
- Handle invalid user input without crashing.

---

# 28. Acceptance Criteria

### Parking

- [ ] A valid vehicle can be parked.
- [ ] A compatible vacant slot is automatically assigned.
- [ ] The assigned slot becomes occupied.
- [ ] A unique ticket is generated.
- [ ] Entry time is recorded.

### Validation

- [ ] Duplicate active vehicles are rejected.
- [ ] Vehicles cannot use incompatible slots.
- [ ] Full parking categories are handled correctly.
- [ ] Invalid ticket numbers are rejected.

### Exit

- [ ] Valid active tickets can be closed.
- [ ] Exit time is recorded.
- [ ] Duration is calculated.
- [ ] Charges are calculated.
- [ ] Slot becomes vacant.
- [ ] Ticket status becomes `DONE`.

### Reporting

- [ ] Parking slots can be displayed.
- [ ] Active tickets can be displayed.
- [ ] Ticket history can be displayed.
- [ ] Parking capacity can be displayed.

---

# 29. Technology Stack

| Component | Technology |
|---|---|
| Programming Language | C++ |
| Standard | C++17 |
| Compiler | GCC / Clang |
| Time Management | `std::chrono` |
| Dynamic Arrays | `std::vector` |
| String Handling | `std::string` |
| Interface | Console |
| Build System | g++ initially |
| Database | None in V1 |

---

# 30. Project Status

**Current Version:** `v1.0`

**Status:** Prototype / Functional Console Application

### Implemented

- [x] Vehicle management
- [x] Parking slot management
- [x] Automatic slot allocation
- [x] Ticket generation
- [x] Entry-time tracking
- [x] Exit-time tracking
- [x] Parking fee calculation
- [x] Active tickets
- [x] Ticket history
- [x] Duplicate vehicle prevention
- [x] Slot release
- [x] Error handling
- [x] Menu-driven interface
- [x] Dynamic memory cleanup

### Planned

- [ ] Persistent storage
- [ ] Configurable parking rates
- [ ] Multiple floors
- [ ] Authentication
- [ ] Payment processing
- [ ] Database integration
- [ ] GUI
- [ ] Reports and analytics
- [ ] REST API
- [ ] Mobile application

---

# 31. License

This project is intended primarily for educational and academic purposes.

A license such as **MIT License** can be added if the project is intended for public distribution.
