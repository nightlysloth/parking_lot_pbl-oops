# Modular Parking Management System (C++)

> **Academic Project-Based Learning (PBL) Documentation**  
> **Course:** Object-Oriented Programming (OOP) / Data Structures  
> **Target Standard:** C++11 or higher  

---

## Table of Contents
1. [Executive Summary](#executive-summary)
2. [Core Concepts & Learning Outcomes](#core-concepts--learning-outcomes)
3. [Project File Architecture](#project-file-architecture)
4. [Detailed Module Breakdown](#detailed-module-breakdown)
5. [System Workflows](#system-workflows)
6. [Business Logic & Pricing Specifications](#business-logic--pricing-specifications)
7. [Compilation & Execution Guide](#compilation--execution-guide)
8. [Future Enhancements](#future-enhancements)
9. [PBL Submission Checklist](#pbl-submission-checklist)

---

## Executive Summary

### Problem Statement
Urban residential complexes, commercial towers, and institutional campuses face significant challenges in managing limited vehicle parking. Manual record-keeping leads to entry delays, inaccurate billing, double-allocation of slots, and poor tracking of active versus historical parking records.

### System Purpose
The **Modular Parking Management System** is a lightweight, console-based desktop application designed to automate the lifecycle of vehicle parking. It handles multi-category vehicle management (Cars, Bikes, Trucks), real-time slot allocation, time-based billing calculations, and historical auditing.

### Academic Objectives (PBL Focus)
This project is structured specifically to demonstrate core **Object-Oriented Programming (OOP)** concepts, modular software design, manual memory management, and file separation in C++. It bridges the gap between basic procedural code and industry-standard multi-file C++ application architecture.

---

## Core Concepts & Learning Outcomes

This project serves as a practical implementation guide for several foundational Computer Science concepts:

+-----------------------------------------------------------------------+
|                         CORE C++ CONCEPTS                             |
+-----------------------------------------------------------------------+
| 1. Object-Oriented Design (Classes, Encapsulation, Composition)        |
| 2. Modular File Architecture (Separate Compilation & Header Guards)    |
| 3. Dynamic Memory Management (Raw Pointers, Heap vs Stack, Destructors)|
| 4. Standard Template Library (STL Containers: std::vector, std::string)|
| 5. System Utilities (std::chrono for time, std::iomanip for formatting)|
| 6. Enums & Strong Typing (enum class for state management)             |
+-----------------------------------------------------------------------+


### 1. Object-Oriented Programming (OOP)
* **Encapsulation:** Combining vehicle state, parking slot states, and ticket data into separate domain objects with defined access scope.
* **Composition & Associations:** Building complex entities by combining simpler ones. A `Ticket` holds references (pointers) to a `vehicle` and a `ParkingSlot`. A `parking` facility contains collections of `ParkingSlot`, `vehicle`, and `Ticket` objects.
* **Resource Management (RAII):** Cleaning up dynamically allocated heap memory in class destructors to prevent memory leaks.

### 2. Modular Architecture & Compilation
* **Header Files (`.h`):** Interface declarations that tell the compiler *what* classes and functions exist without revealing implementation details.
* **Implementation Files (`.cpp`):** Definitions containing operational logic.
* **Header Guards (`#ifndef ... #define ... #endif`):** Preventing multi-definition compile-time errors when headers are included across multiple compilation units.
* **Separate Compilation:** Compiling independent `.cpp` modules into translation units before linking them into a single binary.

### 3. Time Handling (`std::chrono`)
* Utilizing C++11 `<chrono>` library to record system timestamps at entry and exit (`chrono::system_clock::now()`).
* Performing time-delta calculations (`chrono::duration_cast`) to compute exact duration in minutes and rounding up to the nearest hour for billing rules.

---

## Project File Architecture

The codebase is partitioned into **8 files** organized by responsibility:

ParkingManagementSystem/
│
├── Enums.h             # Strongly-typed enumerations & string converter declarations
├── Enums.cpp           # String conversion implementations
│
├── Vehicle.h           # Vehicle domain class representation
├── ParkingSlot.h       # Parking slot state & capacity representation
├── Ticket.h            # Ticket domain entity with timestamps & billing state
│
├── Parking.h           # Parking facility controller class declaration
├── Parking.cpp         # Complete parking business logic implementation
│
└── main.cpp            # Entry point & interactive user interface loop


---

## Detailed Module Breakdown

### Module 1: Enumerations (`Enums.h` & `Enums.cpp`)
* **Objective:** Provides strongly-typed state representations throughout the application to avoid magic strings or numeric flags.
* **Key Components:**
  * `enum class vehicletype`: Represents categories — `car`, `bike`, `truck`.
  * `enum class slotstatus`: Represents slot availability — `vacant`, `reserved`.
  * `enum class ticketstatus`: Represents lifecycle state — `active`, `done`.
* **Helper Functions:**
  * `vehicleTypeToString()`: Converts internal enum value to printable text (`vehicletype::car` -> `"Car"`).
  * `slotStatusToString()`: Maps `vacant` / `reserved` to display string.
  * `ticketStatusToString()`: Maps `active` / `done` to display string.

### Module 2: Vehicle Entity (`Vehicle.h`)
* **Objective:** Defines the data structure representing individual vehicles.
* **Attributes:**
  * `type` (`vehicletype`): Category of vehicle.
  * `reg_number` (`std::string`): License plate / registration string.

### Module 3: Parking Slot Entity (`ParkingSlot.h`)
* **Objective:** Represents a physical parking bay inside the facility.
* **Attributes:**
  * `slotNumber` (`int`): Sequential numerical identifier (e.g., 1 to N).
  * `type` (`vehicletype`): Allowed vehicle category for the bay.
  * `status` (`slotstatus`): Occupancy status (`vacant` vs `reserved`).

### Module 4: Ticket Entity (`Ticket.h`)
* **Objective:** Encapsulates a active or completed parking transaction session.
* **Attributes:**
  * `ticketNumber` (`int`): Auto-incremented unique ticket reference code (e.g., 1001, 1002).
  * `Vehicle` (`vehicle*`): Pointer to the parked vehicle.
  * `slot` (`ParkingSlot*`): Pointer to the assigned slot bay.
  * `charges` (`int`): Total calculated fee upon exit (default `0`).
  * `status` (`ticketstatus`): Ticket state (`active` during parking, `done` after exit).
  * `inTime` / `exitTime` (`std::chrono::system_clock::time_point`): Entry/exit timestamps.

### Module 5: Parking Controller (`Parking.h` & `Parking.cpp`)
* **Objective:** Acts as the central system engine. Manages slot vectors, issues tickets, calculates fees, and handles memory cleanup.
* **Key Methods:**
  * `park(vehicle* v, int ticketid)`: Finds first vacant slot for the vehicle type, reserves it, creates a `Ticket` on the heap, and stores references.
  * `calculateCharges(Ticket* t)`: Calculates duration in minutes, rounds up to billable hours, and applies rates.
  * `unpark(int ticketNumber)`: Marks ticket as completed, frees the slot, and generates a formatted receipt bill.
  * `~parking()`: Destructor that iterates through dynamic lists to `delete` pointers and prevent memory leaks.

### Module 6: Main Program Loop (`main.cpp`)
* **Objective:** Executes the Command-Line Interface (CLI) menu loop, handles input choices, validates duplicate registrations, and controls application workflow.

---

## System Workflows

### 1. Vehicle Check-In Process
[User Selects 'Park Vehicle']
│
▼
[Prompt: Registration Number]
│
▼
[Check: Is Vehicle Currently Parked?]
├── (Yes) ──> [Display Error & Return to Menu]
└── (No)
│
▼
[Prompt: Select Vehicle Type]
│
▼
[Check Slot Availability]
├── (Full) ──> [Display "No Slot Available" & Clean Memory]
└── (Available)
│
▼
[Mark Slot Occupied] ──> [Instantiate Ticket] ──> [Output Ticket Summary]


### 2. Vehicle Checkout & Billing Process
[User Selects 'Exit Vehicle']
│
▼
[Prompt: Enter Ticket Number]
│
▼
[Validate Ticket ID & Status]
├── (Invalid / Closed) ──> [Display Error Message]
└── (Valid Active Ticket)
│
▼
[Capture System Exit Timestamp]
│
▼
[Calculate Duration & Apply Tarif Rate]
│
▼
[Set Ticket = Done | Set Slot = Vacant]
│
▼
[Display Printed Parking Receipt]


---

## Business Logic & Pricing Specifications

| Rule / Parameter | Specification | Implementation Detail |
| :--- | :--- | :--- |
| **Bike Rate** | ₹10 / hour | Evaluated in `calculateCharges()` |
| **Car Rate** | ₹30 / hour | Evaluated in `calculateCharges()` |
| **Truck Rate** | ₹50 / hour | Evaluated in `calculateCharges()` |
| **Minimum Fee** | 1 Hour charge minimum | `if (hours < 1) hours = 1;` |
| **Billing Increment** | Rounded up to next full hour | Formula: `(duration_minutes + 59) / 60` |
| **Duplicate Entry Block** | Active vehicles cannot re-park | Checked in `main.cpp` before slot search |
| **Allocation Policy** | First-Fit Search | First available index in matching vector |

---

## Compilation & Execution Guide

### Prerequisites
* GCC (g++) compiler supporting C++11 or higher installed on your system.

### Build Steps

1. **Clone or download the project files into a single directory.**

2. **Open Terminal / Command Prompt in the project directory.**

3. **Compile all modules together:**
   ```bash
   g++ -std=c++11 main.cpp Parking.cpp Enums.cpp -o parking_system
Run the application:

Linux/macOS:

Bash
./parking_system
Windows:

DOS
parking_system.exe
Future Enhancements
Potential extensions for future development:

File Persistence: Implement std::fstream file I/O to store ticket histories and slot states permanently across app reboots.

Graphical User Interface (GUI): Integrate Qt or SFML to represent parking bays visually as interactive grids.

Dynamic Pricing: Enable surge/peak pricing based on percentage occupancy rates.

PBL Submission Checklist
[x] Modular Structure: Code divided strictly across .h and .cpp files.

[x] Header Guards: Includes #ifndef guards in every header file.

[x] Memory Management: Dynamic objects created with new are properly freed with delete in destructors.

[x] Compilation: Compiles cleanly with standard C++11 compilers without errors.
