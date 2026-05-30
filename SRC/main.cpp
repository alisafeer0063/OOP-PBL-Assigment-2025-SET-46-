#include <iostream>
#include <string>
#include <limits>
#include <memory>

#include "Airline.h"
#include "DomesticFlight.h"
#include "InternationalFlight.h"
#include "CharterFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "FirstClassPassenger.h"
#include "Exceptions.h"

const std::string SAVE_FILE = "data/airline_state.txt";

// ---- input helpers ----

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { clearInput(); return val; }
        clearInput();
        std::cout << "Invalid input. Enter a number.\n";
    }
}

double getDoubleInput(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) { clearInput(); return val; }
        clearInput();
        std::cout << "Invalid input. Enter a number.\n";
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::getline(std::cin, val);
    return val;
}

// ---- sub-menus ----

void addFlightMenu(Airline& airline) {
    std::cout << "\nFlight type: 1) Domestic  2) International  3) Charter\n";
    int type = getIntInput("Choice: ");

    std::string fnum  = getStringInput("Flight number: ");
    std::string orig  = getStringInput("Origin: ");
    std::string dest  = getStringInput("Destination: ");
    std::string date  = getStringInput("Departure date (YYYY-MM-DD): ");
    std::string time  = getStringInput("Departure time (HH:MM): ");
    int seats = getIntInput("Total seats: ");

    try {
        if (type == 1) {
            std::string region = getStringInput("Region (e.g. North/South/East/West): ");
            double fare = getDoubleInput("Base fare ($): ");
            airline.addFlight(std::make_shared<DomesticFlight>(
                fnum, orig, dest, date, time, seats, region, fare));
        } else if (type == 2) {
            std::string country = getStringInput("Destination country: ");
            int visaInt = getIntInput("Visa required? (1=Yes, 0=No): ");
            double fare = getDoubleInput("Base fare ($): ");
            airline.addFlight(std::make_shared<InternationalFlight>(
                fnum, orig, dest, date, time, seats, country, visaInt == 1, fare));
        } else if (type == 3) {
            std::string holder = getStringInput("Contract holder name: ");
            double price = getDoubleInput("Total contract price ($): ");
            airline.addFlight(std::make_shared<CharterFlight>(
                fnum, orig, dest, date, time, seats, holder, price));
        } else {
            std::cout << "Invalid choice.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void searchFlightMenu(Airline& airline) {
    std::cout << "\nSearch by: 1) Flight number  2) Route  3) Date\n";
    int choice = getIntInput("Choice: ");

    try {
        if (choice == 1) {
            std::string fnum = getStringInput("Flight number: ");
            auto f = airline.findFlight(fnum);
            f->displayDetails();
        } else if (choice == 2) {
            std::string orig = getStringInput("Origin: ");
            std::string dest = getStringInput("Destination: ");
            auto results = airline.searchByRoute(orig, dest);
            if (results.empty()) std::cout << "No flights found.\n";
            else for (const auto& f : results) f->displayDetails();
        } else if (choice == 3) {
            std::string date = getStringInput("Date (YYYY-MM-DD): ");
            auto results = airline.searchByDate(date);
            if (results.empty()) std::cout << "No flights on that date.\n";
            else for (const auto& f : results) f->displayDetails();
        } else {
            std::cout << "Invalid choice.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void registerPassengerMenu(Airline& airline) {
    std::cout << "\nPassenger class: 1) Economy  2) Business  3) First Class\n";
    int type = getIntInput("Choice: ");

    std::string pid   = getStringInput("Passenger ID: ");
    std::string name  = getStringInput("Name: ");
    std::string email = getStringInput("Email: ");
    std::string phone = getStringInput("Phone: ");

    try {
        if (type == 1)
            airline.registerPassenger(std::make_shared<EconomyPassenger>(pid, name, email, phone));
        else if (type == 2)
            airline.registerPassenger(std::make_shared<BusinessPassenger>(pid, name, email, phone));
        else if (type == 3)
            airline.registerPassenger(std::make_shared<FirstClassPassenger>(pid, name, email, phone));
        else
            std::cout << "Invalid choice.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void flightMenu(Airline& airline) {
    int choice = 0;
    while (choice != 6) {
        std::cout << "\n-- Flight Management --\n"
                  << "1. Add flight\n"
                  << "2. Remove flight\n"
                  << "3. Search flight\n"
                  << "4. List all flights\n"
                  << "5. Back\n";
        choice = getIntInput("Choice: ");

        if (choice == 1) {
            addFlightMenu(airline);
        } else if (choice == 2) {
            std::string fnum = getStringInput("Flight number to remove: ");
            if (airline.removeFlight(fnum))
                std::cout << "Flight removed.\n";
            else
                std::cout << "Flight not found.\n";
        } else if (choice == 3) {
            searchFlightMenu(airline);
        } else if (choice == 4) {
            airline.listAllFlights();
        } else if (choice == 5) {
            break;
        }
    }
}

void passengerMenu(Airline& airline) {
    int choice = 0;
    while (choice != 5) {
        std::cout << "\n-- Passenger Management --\n"
                  << "1. Register passenger\n"
                  << "2. Remove passenger\n"
                  << "3. View booking history\n"
                  << "4. List all passengers\n"
                  << "5. Back\n";
        choice = getIntInput("Choice: ");

        if (choice == 1) {
            registerPassengerMenu(airline);
        } else if (choice == 2) {
            std::string pid = getStringInput("Passenger ID to remove: ");
            if (airline.removePassenger(pid))
                std::cout << "Passenger removed.\n";
            else
                std::cout << "Passenger not found.\n";
        } else if (choice == 3) {
            std::string pid = getStringInput("Passenger ID: ");
            try { airline.viewBookingHistory(pid); }
            catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
        } else if (choice == 4) {
            airline.listAllPassengers();
        } else if (choice == 5) {
            break;
        }
    }
}

void bookingMenu(Airline& airline) {
    int choice = 0;
    while (choice != 3) {
        std::cout << "\n-- Booking --\n"
                  << "1. Book ticket\n"
                  << "2. Cancel ticket\n"
                  << "3. Back\n";
        choice = getIntInput("Choice: ");

        if (choice == 1) {
            std::string pid  = getStringInput("Passenger ID: ");
            std::string fnum = getStringInput("Flight number: ");
            try { airline.bookTicket(pid, fnum); }
            catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
        } else if (choice == 2) {
            std::string tid = getStringInput("Ticket ID to cancel: ");
            try { airline.cancelTicket(tid); }
            catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
        } else if (choice == 3) {
            break;
        }
    }
}

void reportsMenu(Airline& airline) {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n-- Reports --\n"
                  << "1. Today's departures\n"
                  << "2. Occupancy per flight\n"
                  << "3. Top 5 revenue flights\n"
                  << "4. Back\n";
        choice = getIntInput("Choice: ");

        if (choice == 1) {
            std::string today = getStringInput("Enter today's date (YYYY-MM-DD): ");
            airline.reportTodaysDepartures(today);
        } else if (choice == 2) {
            airline.reportOccupancy();
        } else if (choice == 3) {
            airline.reportTopRevenueFlights();
        } else if (choice == 4) {
            break;
        }
    }
}

// ---- main ----

int main() {
    Airline airline("SkyLink Airways");

    airline.loadFromFile(SAVE_FILE);

    int choice = 0;
    while (choice != 6) {
        std::cout << "\n====== SkyLink Airways ======\n"
                  << "1. Flight Management\n"
                  << "2. Passenger Management\n"
                  << "3. Booking & Cancellation\n"
                  << "4. Reports\n"
                  << "5. Save & Exit\n"
                  << "6. Exit without saving\n";
        choice = getIntInput("Choice: ");

        if (choice == 1) {
            flightMenu(airline);
        } else if (choice == 2) {
            passengerMenu(airline);
        } else if (choice == 3) {
            bookingMenu(airline);
        } else if (choice == 4) {
            reportsMenu(airline);
        } else if (choice == 5) {
            airline.saveToFile(SAVE_FILE);
            std::cout << "Goodbye.\n";
            return 0;
        } else if (choice == 6) {
            std::cout << "Exiting without save.\n";
            return 0;
        }
    }

    return 0;
}
