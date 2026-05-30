# SkyLink Airways - Airline Reservation System

Student ID: 2025-SET-46

## Requirements

- g++ with C++17 support
- GNU Make

## How to Build

```
make
```

This compiles all source files and produces the `skylink` executable.

## How to Run

```
make run
```

or directly:

```
./skylink
```

The program looks for `data/airline_state.txt` on startup. If the file is not found, it starts with an empty state. A sample data file is provided at `data/sample_data.txt`. To load the sample data, copy it:

```
cp data/sample_data.txt data/airline_state.txt
./skylink
```

## How to Clean

```
make clean
```

## File Structure

```
OOP_PBL_2025-SET-46/
├── src/
│   ├── main.cpp
│   ├── Flight.h / Flight.cpp
│   ├── DomesticFlight.h / DomesticFlight.cpp
│   ├── InternationalFlight.h / InternationalFlight.cpp
│   ├── CharterFlight.h / CharterFlight.cpp
│   ├── Passenger.h / Passenger.cpp
│   ├── EconomyPassenger.h / EconomyPassenger.cpp
│   ├── BusinessPassenger.h / BusinessPassenger.cpp
│   ├── FirstClassPassenger.h / FirstClassPassenger.cpp
│   ├── Ticket.h / Ticket.cpp
│   ├── Airline.h / Airline.cpp
│   ├── SearchUtil.h
│   └── Exceptions.h
├── data/
│   └── sample_data.txt
├── docs/
│   └── Design_Report.pdf
├── Makefile
└── README.md
```

## Menu Overview

1. Flight Management - add, remove, search, list flights
2. Passenger Management - register, remove, view history
3. Booking and Cancellation - book a ticket, cancel with refund
4. Reports - today's departures, occupancy, top revenue
5. Save and Exit - writes full state to disk
6. Exit without saving
