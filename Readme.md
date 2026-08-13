# Product Requirements Document — Parking Management System

**Project Type:** PBL / Academic Software Project  
**Technology:** C++  
**Architecture:** Object-Oriented Programming (OOP)  
**Interface:** Console / Terminal  
**Target Environment:** Desktop  
**Version:** 1.0  
**Status:** Project Specification

---

## 1. Executive Summary

The **Parking Management System (PMS)** is a console-based C++ application designed to manage vehicle parking in a residential society, building, or small parking facility.

The system automates basic parking operations such as:

- Vehicle entry
- Parking-slot allocation
- Ticket generation
- Vehicle exit
- Parking-fee calculation
- Slot availability tracking
- Active-ticket management
- Ticket history

The project demonstrates practical implementation of **Object-Oriented Programming, classes, objects, enumerations, vectors, pointers, functions, and basic time handling in C++**.

> **Core Principle:** Keep the system functional, structured, and easy to demonstrate without introducing unnecessary enterprise-level complexity.

---

# 2. Problem Statement

Traditional parking management in small facilities may rely on manual registers or verbal coordination.

This can lead to:

- Difficulty tracking available slots
- Duplicate parking records
- Manual calculation errors
- Difficulty identifying occupied slots
- Lack of organized ticket records
- Inefficient vehicle exit handling

The proposed system provides a simple computerized solution for managing these operations.

---

# 3. Project Objectives

| Objective | Description |
|---|---|
| Slot Management | Track vacant and occupied parking slots |
| Vehicle Management | Store vehicle registration numbers and types |
| Ticket Management | Generate and track parking tickets |
| Automated Allocation | Assign suitable vacant slots automatically |
| Billing | Calculate parking charges based on duration |
| Tracking | Maintain active and completed ticket records |
| OOP Demonstration | Apply classes, objects, pointers, vectors, and enums |
| Usability | Provide a clear menu-driven interface |

---

# 4. Scope

### In Scope

- Cars
- Bikes
- Trucks
- Separate slots for each vehicle type
- Automatic slot allocation
- Ticket generation
- Entry-time recording
- Exit-time recording
- Hourly billing
- Slot status management
- Active-ticket display
- Ticket history
- Parking information display
- Console-based interaction

### Out of Scope

The first version will **not** include:

- Online payments
- Mobile applications
- Web dashboards
- RFID integration
- Number-plate recognition
- Database servers
- Cloud deployment
- SMS/email notifications
- User accounts
- Real-time sensors
- Multi-location management

---

# 5. Target Users

| User | Responsibility |
|---|---|
| Parking Operator | Manage vehicle entry and exit |
| Security Staff | Issue/check parking tickets |
| Administrator | View parking status and records |
| Visitor | Park and retrieve vehicle |

The current implementation can operate primarily through a **single operator interface**.

---

# 6. System Overview

```text
                 ┌───────────────────────┐
                 │ Parking Management    │
                 │       System          │
                 └───────────┬───────────┘
                             │
          ┌──────────────────┼──────────────────┐
          │                  │                  │
          ▼                  ▼                  ▼
     Vehicle Module     Slot Module       Ticket Module
          │                  │                  │
          ▼                  ▼                  ▼
     Vehicle Data       Slot Status       Entry / Exit
                             │                  │
                             └────────┬─────────┘
                                      ▼
                              Billing Module
```

---

# 7. Functional Requirements

## FR-01 — Vehicle Registration

The system shall allow the operator to enter:

- Vehicle registration number
- Vehicle type

Supported types:

- Car
- Bike
- Truck

Example:

```text
Registration Number: UP14AB1234
Vehicle Type: Car
```

---

## FR-02 — Parking Slot Allocation

When a vehicle enters, the system shall:

1. Identify the vehicle type.
2. Select the corresponding slot collection.
3. Search for a vacant slot.
4. Assign the first available slot.
5. Mark the slot as occupied/reserved.
6. Generate a parking ticket.

---

## FR-03 — Ticket Generation

Each successful parking operation shall generate a unique ticket number.

Example:

```text
Ticket Number : 1001
Vehicle       : UP14AB1234
Type          : Car
Slot          : 3
Status        : Active
```

---

## FR-04 — Entry Time

The system shall automatically record the vehicle's entry time using the C++ `chrono` library.

The operator should not need to manually enter the time.

---

## FR-05 — Vehicle Exit

The operator shall enter the ticket number when a vehicle leaves.

The system shall:

1. Locate the ticket.
2. Verify that it is active.
3. Record the exit time.
4. Calculate parking duration.
5. Calculate charges.
6. Mark the ticket as completed.
7. Make the slot vacant.
8. Display the final bill.

---

# 8. Billing Requirements

Parking charges shall be calculated according to vehicle type.

### Proposed Rates

| Vehicle Type | Rate / Hour |
|---|---:|
| 🏍 Bike | ₹10 |
| 🚗 Car | ₹30 |
| 🚚 Truck | ₹50 |

### Billing Rule

The system charges by **started hours**.

| Parking Duration | Charged Hours |
|---:|---:|
| 10 min | 1 |
| 30 min | 1 |
| 60 min | 1 |
| 61 min | 2 |
| 120 min | 2 |
| 121 min | 3 |

### Formula

```text
Charged Hours = Ceiling(Duration in Minutes / 60)

Total Fee = Charged Hours × Vehicle Rate
```

---

# 9. Slot Management

Each parking slot contains:

| Attribute | Description |
|---|---|
| Slot Number | Unique number within its category |
| Vehicle Type | Type of vehicle accepted |
| Status | Vacant or Reserved |

Example:

```text
CAR SLOTS

Slot 1 → Vacant
Slot 2 → Reserved
Slot 3 → Vacant
Slot 4 → Reserved
Slot 5 → Vacant
```

---

# 10. Vehicle Types

```text
                VEHICLE
                   │
        ┌──────────┼──────────┐
        │          │          │
       CAR        BIKE      TRUCK
```

Each vehicle type has its own parking-slot vector.

```cpp
vector<ParkingSlot> carslots;
vector<ParkingSlot> bikeslots;
vector<ParkingSlot> truckslots;
```

---

# 11. Ticket Lifecycle

```text
             ┌─────────────┐
             │   Created   │
             └──────┬──────┘
                    │
                    ▼
             ┌─────────────┐
             │    ACTIVE   │
             └──────┬──────┘
                    │
             Vehicle Exits
                    │
                    ▼
             ┌─────────────┐
             │     DONE    │
             └─────────────┘
```

A completed ticket shall not be usable for another exit operation.

---

# 12. Core Classes

The project shall use the following major classes:

| Class | Responsibility |
|---|---|
| `vehicle` | Stores vehicle information |
| `ParkingSlot` | Represents an individual parking slot |
| `Ticket` | Stores parking transaction information |
| `parking` | Controls parking operations |

---

# 13. Vehicle Class

### Purpose

Represent a vehicle entering the parking facility.

### Attributes

| Attribute | Type |
|---|---|
| `type` | `vehicletype` |
| `reg_number` | `string` |

### Example

```cpp
vehicle car(
    vehicletype::car,
    "UP14AB1234"
);
```

---

# 14. ParkingSlot Class

### Purpose

Represent a physical parking slot.

### Attributes

| Attribute | Type |
|---|---|
| `slotNumber` | `int` |
| `type` | `vehicletype` |
| `status` | `slotstatus` |

---

# 15. Ticket Class

### Purpose

Represent a parking transaction.

### Attributes

| Attribute | Type |
|---|---|
| `ticketNumber` | `int` |
| `Vehicle` | `vehicle*` |
| `slot` | `ParkingSlot*` |
| `charges` | `int` |
| `status` | `ticketstatus` |
| `inTime` | `chrono::system_clock::time_point` |
| `exitTime` | `chrono::system_clock::time_point` |

---

# 16. Parking Class

The `parking` class acts as the primary management class.

### Responsibilities

- Store parking information
- Create parking slots
- Allocate slots
- Create tickets
- Find tickets
- Process vehicle exits
- Calculate charges
- Display slot status
- Display active tickets
- Display ticket history

---

# 17. Enumerations

The project shall use enumerations to represent fixed states.

### Vehicle Type

```cpp
enum class vehicletype {
    car,
    bike,
    truck
};
```

### Slot Status

```cpp
enum class slotstatus {
    reserved,
    vacant
};
```

### Ticket Status

```cpp
enum class ticketstatus {
    active,
    done
};
```

---

# 18. Main Menu

The application shall provide a menu similar to:

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

====================================
Enter your choice:
```

---

# 19. Park Vehicle Flow

```text
START
  │
  ▼
Enter Registration Number
  │
  ▼
Select Vehicle Type
  │
  ▼
Check Available Slot
  │
  ├── No ──► Display "No Slot Available"
  │
  ▼
Assign Slot
  │
  ▼
Generate Ticket
  │
  ▼
Record Entry Time
  │
  ▼
Display Ticket
  │
  ▼
END
```

---

# 20. Exit Vehicle Flow

```text
START
  │
  ▼
Enter Ticket Number
  │
  ▼
Find Ticket
  │
  ├── Invalid ──► Error Message
  │
  ▼
Check Ticket Status
  │
  ├── Done ──► Already Completed
  │
  ▼
Record Exit Time
  │
  ▼
Calculate Duration
  │
  ▼
Calculate Charges
  │
  ▼
Free Parking Slot
  │
  ▼
Mark Ticket DONE
  │
  ▼
Display Bill
  │
  ▼
END
```

---

# 21. Parking Information

The system shall display:

```text
====================================
        PARKING INFORMATION
====================================

Society : ABC Residency
Tower   : Tower A

Capacity:
Cars    : 5
Bikes   : 10
Trucks  : 3
```

---

# 22. Parking Slot Display

The system shall provide a complete view of slot availability.

Example:

```text
====================================
        PARKING SLOT STATUS
====================================

--- CAR SLOTS ---
Slot 1 : Vacant
Slot 2 : Reserved
Slot 3 : Vacant
Slot 4 : Reserved
Slot 5 : Vacant

--- BIKE SLOTS ---
Slot 1 : Vacant
Slot 2 : Vacant
Slot 3 : Reserved
...
```

---

# 23. Active Ticket Display

The system shall display currently active parking transactions.

Example:

```text
====================================
          ACTIVE TICKETS
====================================

Ticket Number : 1001
Vehicle Number: UP14AB1234
Vehicle Type  : Car
Slot Number   : 2
Status        : Active
```

---

# 24. Ticket History

The system shall maintain completed and active tickets during the program's execution.

Example:

| Ticket | Vehicle | Type | Slot | Status | Charges |
|---:|---|---|---:|---|---:|
| 1001 | UP14AB1234 | Car | 2 | Done | ₹60 |
| 1002 | UP15XY5678 | Bike | 1 | Active | — |
| 1003 | DL01AA1234 | Truck | 1 | Done | ₹100 |

---

# 25. Data Structures

The project shall primarily use C++ STL vectors.

```cpp
vector<ParkingSlot> carslots;
vector<ParkingSlot> bikeslots;
vector<ParkingSlot> truckslots;

vector<vehicle*> vehicles;
vector<Ticket*> tickets;
```

### Reason

Vectors provide a simple way to:

- Store multiple objects
- Iterate through records
- Search for available slots
- Maintain ticket history

---

# 26. Memory Management

The current implementation uses dynamically allocated objects:

```cpp
new vehicle(...)
new Ticket(...)
```

The `parking` destructor shall release allocated memory:

```cpp
delete v;
delete t;
```

This prevents unnecessary memory leaks during normal program termination.

---

# 27. Error Handling

The system shall handle common invalid operations.

| Situation | Expected Response |
|---|---|
| Invalid menu choice | Display error |
| No parking slot | Display unavailable message |
| Invalid ticket number | Display error |
| Already completed ticket | Reject operation |
| Duplicate active vehicle | Reject parking |
| Empty parking history | Display appropriate message |

---

# 28. Non-Functional Requirements

| Requirement | Description |
|---|---|
| Simplicity | Interface should remain straightforward |
| Reliability | Basic operations should produce consistent results |
| Readability | Code should be separated into logical classes/functions |
| Maintainability | New vehicle types/rates should be easy to add |
| Portability | Program should compile using a standard C++ compiler |
| Performance | Suitable for a small parking facility |
| Usability | Menu and output should be easy to understand |

---

# 29. Suggested Project Capacity

For demonstration purposes:

| Vehicle | Capacity |
|---|---:|
| Cars | 5 |
| Bikes | 10 |
| Trucks | 3 |
| **Total** | **18** |

These values can be changed through the `parking` constructor.

---

# 30. Technology Stack

| Component | Technology |
|---|---|
| Programming Language | C++ |
| Standard Library | STL |
| Data Structures | `vector` |
| Time Management | `chrono` |
| Input/Output | `iostream` |
| String Handling | `string` |
| Formatting | `iomanip` |
| Memory | Dynamic allocation |
| Interface | Command Line / Terminal |
| Paradigm | Object-Oriented Programming |

---

# 31. OOP Concepts Demonstrated

The project should demonstrate the following concepts:

### Classes and Objects

```text
vehicle
ParkingSlot
Ticket
parking
```

### Encapsulation

Data and operations are grouped within classes.

### Constructors

Used to initialize objects.

### Pointers

Used to establish relationships between:

```text
Ticket → Vehicle
Ticket → ParkingSlot
```

### Composition / Association

A parking system manages multiple:

- Vehicles
- Slots
- Tickets

### Enumerations

Used for controlled states.

### STL

`vector` is used for dynamic collections.

---

# 32. Basic System Architecture

```text
┌──────────────────────────────────────────┐
│              MAIN PROGRAM                │
│              main.cpp                    │
└──────────────────┬───────────────────────┘
                   │
                   ▼
┌──────────────────────────────────────────┐
│              PARKING CLASS               │
│                                          │
│  park()                                  │
│  unpark()                                │
│  calculateCharges()                      │
│  findTicket()                            │
│  displaySlots()                          │
│  displayActiveTickets()                 │
└───────────────┬───────────────┬──────────┘
                │               │
                ▼               ▼
        ┌─────────────┐   ┌─────────────┐
        │   Vehicle   │   │ ParkingSlot │
        └─────────────┘   └─────────────┘
                │               │
                └───────┬───────┘
                        ▼
                 ┌─────────────┐
                 │   Ticket    │
                 └─────────────┘
```

---

# 33. Project Workflow

### Phase 1 — Design

- Define project requirements
- Define vehicle types
- Define slot states
- Define ticket states
- Design class structure

### Phase 2 — Implementation

- Implement classes
- Implement slot creation
- Implement vehicle parking
- Implement ticket generation
- Implement vehicle exit
- Implement billing

### Phase 3 — Testing

- Test successful parking
- Test full parking
- Test vehicle exit
- Test invalid tickets
- Test duplicate vehicles
- Test billing

### Phase 4 — Demonstration

- Show system initialization
- Park multiple vehicles
- Display slots
- Exit a vehicle
- Display generated bill
- Display ticket history

---

# 34. Testing Plan

| Test Case | Input | Expected Result |
|---|---|---|
| TC-01 | Valid car | Car gets available slot |
| TC-02 | Valid bike | Bike gets available slot |
| TC-03 | Valid truck | Truck gets available slot |
| TC-04 | Full car parking | No slot available |
| TC-05 | Valid ticket | Vehicle exits |
| TC-06 | Invalid ticket | Error displayed |
| TC-07 | Completed ticket | Exit rejected |
| TC-08 | Duplicate active vehicle | Parking rejected |
| TC-09 | Display slots | Correct slot status |
| TC-10 | Display history | Ticket records displayed |

---

# 35. Sample Scenario

### Step 1 — Car Enters

```text
Registration: UP14AB1234
Type: Car
```

System assigns:

```text
Slot: 1
Ticket: 1001
Status: Active
```

### Step 2 — Another Vehicle Enters

```text
Registration: UP14CD5678
Type: Bike
```

System assigns:

```text
Slot: 1
Ticket: 1002
Status: Active
```

Slots now show:

```text
Car Slot 1  → Reserved
Bike Slot 1 → Reserved
```

### Step 3 — Car Exits

Operator enters:

```text
Ticket: 1001
```

System:

```text
Calculates duration
       ↓
Calculates fee
       ↓
Marks ticket DONE
       ↓
Frees Car Slot 1
       ↓
Displays bill
```

---

# 36. Expected Bill

```text
====================================
           PARKING BILL
====================================

Ticket Number : 1001
Vehicle Number: UP14AB1234
Vehicle Type  : Car
Slot Number   : 1

Duration      : 95 minutes
Charged Hours : 2

Total Charges : ₹60

====================================
Vehicle exited successfully.
```

---

# 37. Future Enhancements

The following features may be considered in future versions:

| Feature | Priority |
|---|---|
| File-based data storage | Medium |
| Admin login | Medium |
| Multiple parking floors | Medium |
| Monthly parking passes | Medium |
| Receipt export | Low |
| Database integration | Low |
| GUI application | Low |
| QR-code tickets | Low |
| Online payment | Low |
| Number-plate recognition | Low |

These are **future enhancements**, not requirements for Version 1.0.

---

# 38. Success Criteria

The project will be considered successful if it can:

- [x] Create parking slots
- [x] Accept vehicle details
- [x] Allocate suitable vacant slots
- [x] Generate unique tickets
- [x] Record entry time
- [x] Process vehicle exits
- [x] Calculate parking charges
- [x] Free occupied slots
- [x] Display active tickets
- [x] Display ticket history
- [x] Handle common invalid inputs
- [x] Demonstrate core OOP concepts

---

# 39. Project Deliverables

The final PBL submission should contain:

```text
Parking Management System
│
├── Source Code
│   └── main.cpp
│
├── Project Report
│
├── PRD
│
├── Class Diagram
│
├── Flowchart
│
├── Test Cases
│
├── Screenshots
│
└── Presentation
```

---

# 40. Final Product Definition

> **Parking Management System** is a C++ console application that provides a structured way to manage parking slots, vehicles, tickets, vehicle entry/exit, and parking fees.

The system focuses on a **small-scale parking facility** and demonstrates practical application of C++ OOP and STL concepts without introducing unnecessary external infrastructure.

**Version 1.0 → Functional, console-based, self-contained, and suitable for PBL demonstration.**
