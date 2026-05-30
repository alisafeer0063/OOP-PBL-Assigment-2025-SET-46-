#include "Airline.h"
#include "Exceptions.h"
#include "DomesticFlight.h"
#include "InternationalFlight.h"
#include "CharterFlight.h"
#include "EconomyPassenger.h"
#include "BusinessPassenger.h"
#include "FirstClassPassenger.h"
#include "SearchUtil.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <stdexcept>

// ---- helpers ----

std::string Airline::generateTicketID() const {
    return "TKT" + std::to_string(tickets.size() + 1);
}

int Airline::nextSeatFor(const std::string& flightNumber) const {
    int maxSeat = 0;
    for (const auto& t : tickets) {
        if (t.getFlightNumber() == flightNumber &&
            t.getStatus() == BookingStatus::CONFIRMED) {
            if (t.getSeatNumber() > maxSeat)
                maxSeat = t.getSeatNumber();
        }
    }
    return maxSeat + 1;
}

int Airline::daysUntilDeparture(const std::string& depDate) const {
    // parse YYYY-MM-DD
    int year = 0, month = 0, day = 0;
    sscanf(depDate.c_str(), "%d-%d-%d", &year, &month, &day);

    std::tm dep = {};
    dep.tm_year = year - 1900;
    dep.tm_mon  = month - 1;
    dep.tm_mday = day;
    std::time_t depTime = std::mktime(&dep);

    std::time_t now = std::time(nullptr);
    double diff = std::difftime(depTime, now);
    int days = static_cast<int>(diff / 86400);
    return (days < 0) ? 0 : days;
}

// ---- constructor ----

Airline::Airline(const std::string& name) : airlineName(name) {}

// ---- flight management ----

void Airline::addFlight(std::shared_ptr<Flight> flight) {
    for (const auto& f : flights) {
        if (f->getFlightNumber() == flight->getFlightNumber())
            throw std::runtime_error("Flight " + flight->getFlightNumber() + " already exists.");
    }
    flights.push_back(flight);
    std::cout << "Flight " << flight->getFlightNumber() << " added.\n";
}

bool Airline::removeFlight(const std::string& flightNumber) {
    auto it = std::find_if(flights.begin(), flights.end(),
        [&](const std::shared_ptr<Flight>& f) {
            return f->getFlightNumber() == flightNumber;
        });
    if (it == flights.end()) return false;
    flights.erase(it);
    return true;
}

std::shared_ptr<Flight> Airline::findFlight(const std::string& flightNumber) const {
    auto results = searchByField<Flight>(flights, flightNumber, &Flight::getFlightNumber);
    if (results.empty())
        throw NotFoundException("Flight " + flightNumber);
    return results[0];
}

std::vector<std::shared_ptr<Flight>> Airline::searchByRoute(const std::string& origin,
                                                             const std::string& dest) const {
    std::vector<std::shared_ptr<Flight>> result;
    for (const auto& f : flights) {
        if (f->getOrigin() == origin && f->getDestination() == dest)
            result.push_back(f);
    }
    return result;
}

std::vector<std::shared_ptr<Flight>> Airline::searchByDate(const std::string& date) const {
    return searchByField<Flight>(flights, date, &Flight::getDepartureDate);
}

void Airline::listAllFlights() const {
    if (flights.empty()) {
        std::cout << "No flights registered.\n";
        return;
    }
    std::cout << "--- All Flights ---\n";
    for (const auto& f : flights)
        f->displayDetails();
}

// ---- passenger management ----

void Airline::registerPassenger(std::shared_ptr<Passenger> p) {
    for (const auto& existing : passengers) {
        if (existing->getPassengerID() == p->getPassengerID())
            throw std::runtime_error("Passenger ID " + p->getPassengerID() + " already exists.");
    }
    passengers.push_back(p);
    std::cout << "Passenger " << p->getName() << " registered.\n";
}

bool Airline::removePassenger(const std::string& passengerID) {
    auto it = std::find_if(passengers.begin(), passengers.end(),
        [&](const std::shared_ptr<Passenger>& p) {
            return p->getPassengerID() == passengerID;
        });
    if (it == passengers.end()) return false;
    passengers.erase(it);
    return true;
}

std::shared_ptr<Passenger> Airline::findPassenger(const std::string& passengerID) const {
    auto results = searchByField<Passenger>(passengers, passengerID, &Passenger::getPassengerID);
    if (results.empty())
        throw NotFoundException("Passenger " + passengerID);
    return results[0];
}

void Airline::viewBookingHistory(const std::string& passengerID) const {
    auto p = findPassenger(passengerID);
    std::cout << "Booking history for " << p->getName() << ":\n";
    bool found = false;
    for (const auto& t : tickets) {
        if (t.getPassengerID() == passengerID) {
            std::cout << "  " << t << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "  No bookings found.\n";
}

void Airline::listAllPassengers() const {
    if (passengers.empty()) {
        std::cout << "No passengers registered.\n";
        return;
    }
    std::cout << "--- All Passengers ---\n";
    for (const auto& p : passengers)
        p->displayDetails();
}

// ---- booking ----

Ticket Airline::bookTicket(const std::string& passengerID, const std::string& flightNumber) {
    auto passenger = findPassenger(passengerID);
    auto flight    = findFlight(flightNumber);

    // check duplicate booking
    for (const auto& t : tickets) {
        if (t.getPassengerID() == passengerID &&
            t.getFlightNumber() == flightNumber &&
            t.getStatus() == BookingStatus::CONFIRMED) {
            throw DuplicateBookingException(passengerID, flightNumber);
        }
    }

    // check seat availability
    if (flight->getAvailableSeats() <= 0)
        throw FlightFullException(flightNumber);

    flight->bookSeat();

    double fare = flight->calculateBaseFare();
    int seat = nextSeatFor(flightNumber);

    Ticket t(generateTicketID(), passengerID, flightNumber, seat, fare);
    tickets.push_back(t);

    // award loyalty points: fare * multiplier, truncated to int
    int pts = static_cast<int>(fare * passenger->getLoyaltyMultiplier() / 10.0);
    passenger->addLoyaltyPoints(pts);

    std::cout << "Booking confirmed: " << t << "\n";
    return t;
}

// ---- cancellation ----

double Airline::cancelTicket(const std::string& ticketID) {
    auto it = std::find_if(tickets.begin(), tickets.end(),
        [&](const Ticket& t) { return t.getTicketID() == ticketID; });

    if (it == tickets.end())
        throw InvalidCancellationException("Ticket " + ticketID + " not found.");

    if (it->getStatus() == BookingStatus::CANCELLED)
        throw InvalidCancellationException("Ticket " + ticketID + " is already cancelled.");

    auto flight    = findFlight(it->getFlightNumber());
    auto passenger = findPassenger(it->getPassengerID());

    int days = daysUntilDeparture(flight->getDepartureDate());
    double refundPct = passenger->getRefundPercent(days);
    double refund = it->getFarePaid() * refundPct;

    it->cancel();
    flight->releaseSeat();

    std::cout << "Ticket " << ticketID << " cancelled. Refund: $"
              << std::fixed << std::setprecision(2) << refund
              << " (" << (int)(refundPct * 100) << "% of $"
              << it->getFarePaid() << ")\n";
    return refund;
}

// ---- reports ----

void Airline::reportTodaysDepartures(const std::string& today) const {
    std::cout << "--- Departures on " << today << " ---\n";
    bool found = false;
    for (const auto& f : flights) {
        if (f->getDepartureDate() == today) {
            f->displayDetails();
            found = true;
        }
    }
    if (!found) std::cout << "No departures today.\n";
}

void Airline::reportOccupancy() const {
    std::cout << "--- Flight Occupancy ---\n";
    for (const auto& f : flights) {
        std::cout << f->getFlightNumber() << " ("
                  << f->getOrigin() << "->" << f->getDestination() << "): "
                  << std::fixed << std::setprecision(1)
                  << f->getOccupancyPercent() << "%\n";
    }
}

void Airline::reportTopRevenueFlights() const {
    // build a map: flightNumber -> total revenue from confirmed tickets
    std::map<std::string, double> revenue;
    for (const auto& f : flights)
        revenue[f->getFlightNumber()] = 0.0;

    for (const auto& t : tickets) {
        if (t.getStatus() == BookingStatus::CONFIRMED)
            revenue[t.getFlightNumber()] += t.getFarePaid();
    }

    // sort by revenue descending
    std::vector<std::pair<std::string, double>> sorted(revenue.begin(), revenue.end());
    std::sort(sorted.begin(), sorted.end(),
        [](const std::pair<std::string,double>& a, const std::pair<std::string,double>& b) {
            return a.second > b.second;
        });

    std::cout << "--- Top 5 Revenue Flights ---\n";
    int count = 0;
    for (const auto& entry : sorted) {
        if (count >= 5) break;
        std::cout << (count + 1) << ". Flight " << entry.first
                  << " - $" << std::fixed << std::setprecision(2) << entry.second << "\n";
        count++;
    }
}

// ---- persistence ----

void Airline::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Could not open file for saving: " << filename << "\n";
        return;
    }

    // save flights
    out << "FLIGHTS " << flights.size() << "\n";
    for (const auto& f : flights) {
        out << f->getType() << "|"
            << f->getFlightNumber() << "|"
            << f->getOrigin() << "|"
            << f->getDestination() << "|"
            << f->getDepartureDate() << "|"
            << f->getDepartureTime() << "|"
            << f->getTotalSeats() << "|"
            << f->getAvailableSeats() << "|";

        // For charter: store per-seat fare (calculateBaseFare returns contractPrice/seats)
        // On load we multiply back: perSeatFare * totalSeats = contractPrice
        out << f->calculateBaseFare() << "|"
            << f->extraInfo() << "\n";
    }

    // save passengers
    out << "PASSENGERS " << passengers.size() << "\n";
    for (const auto& p : passengers) {
        out << p->getPassengerClass() << "|"
            << p->getPassengerID() << "|"
            << p->getName() << "|"
            << p->getEmail() << "|"
            << p->getPhone() << "|"
            << p->getLoyaltyPoints() << "\n";
    }

    // save tickets
    out << "TICKETS " << tickets.size() << "\n";
    for (const auto& t : tickets) {
        out << t.getTicketID() << "|"
            << t.getPassengerID() << "|"
            << t.getFlightNumber() << "|"
            << t.getSeatNumber() << "|"
            << t.getFarePaid() << "|"
            << t.getStatusString() << "\n";
    }

    out.close();
    std::cout << "State saved to " << filename << "\n";
}

void Airline::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "No save file found. Starting fresh.\n";
        return;
    }

    flights.clear();
    passengers.clear();
    tickets.clear();

    std::string line;

    // --- load flights ---
    std::getline(in, line);
    int flightCount = 0;
    sscanf(line.c_str(), "FLIGHTS %d", &flightCount);

    for (int i = 0; i < flightCount; i++) {
        std::getline(in, line);
        std::istringstream ss(line);
        std::string type, fnum, orig, dest, date, time, extra;
        int totalSeats, availSeats;
        double baseFare;

        std::getline(ss, type,       '|');
        std::getline(ss, fnum,       '|');
        std::getline(ss, orig,       '|');
        std::getline(ss, dest,       '|');
        std::getline(ss, date,       '|');
        std::getline(ss, time,       '|');
        std::string ts, as, bf;
        std::getline(ss, ts,         '|');
        std::getline(ss, as,         '|');
        std::getline(ss, bf,         '|');
        std::getline(ss, extra);

        totalSeats = std::stoi(ts);
        availSeats = std::stoi(as);
        baseFare   = std::stod(bf);

        std::shared_ptr<Flight> flight;
        if (type == "Domestic") {
            flight = std::make_shared<DomesticFlight>(fnum, orig, dest, date, time,
                                                       totalSeats, extra, baseFare);
        } else if (type == "International") {
            // extra = "CountryName,visaFlag"
            size_t comma = extra.find(',');
            std::string country = extra.substr(0, comma);
            bool visa = (extra.substr(comma + 1) == "1");
            flight = std::make_shared<InternationalFlight>(fnum, orig, dest, date, time,
                                                            totalSeats, country, visa, baseFare);
        } else {
            // Charter: baseFare column holds contractPrice, extra = holder name
            flight = std::make_shared<CharterFlight>(fnum, orig, dest, date, time,
                                                      totalSeats, extra, baseFare * totalSeats);
        }

        // restore available seats by booking the difference
        int booked = totalSeats - availSeats;
        for (int s = 0; s < booked; s++)
            flight->bookSeat();

        flights.push_back(flight);
    }

    // --- load passengers ---
    std::getline(in, line);
    int passengerCount = 0;
    sscanf(line.c_str(), "PASSENGERS %d", &passengerCount);

    for (int i = 0; i < passengerCount; i++) {
        std::getline(in, line);
        std::istringstream ss(line);
        std::string cls, pid, name, email, phone, pts;

        std::getline(ss, cls,   '|');
        std::getline(ss, pid,   '|');
        std::getline(ss, name,  '|');
        std::getline(ss, email, '|');
        std::getline(ss, phone, '|');
        std::getline(ss, pts);

        std::shared_ptr<Passenger> p;
        if (cls == "Economy")
            p = std::make_shared<EconomyPassenger>(pid, name, email, phone);
        else if (cls == "Business")
            p = std::make_shared<BusinessPassenger>(pid, name, email, phone);
        else
            p = std::make_shared<FirstClassPassenger>(pid, name, email, phone);

        p->addLoyaltyPoints(std::stoi(pts));
        passengers.push_back(p);
    }

    // --- load tickets ---
    std::getline(in, line);
    int ticketCount = 0;
    sscanf(line.c_str(), "TICKETS %d", &ticketCount);

    for (int i = 0; i < ticketCount; i++) {
        std::getline(in, line);
        std::istringstream ss(line);
        std::string tid, pid, fnum, seat, fare, status;

        std::getline(ss, tid,    '|');
        std::getline(ss, pid,    '|');
        std::getline(ss, fnum,   '|');
        std::getline(ss, seat,   '|');
        std::getline(ss, fare,   '|');
        std::getline(ss, status);

        Ticket t(tid, pid, fnum, std::stoi(seat), std::stod(fare));
        if (status == "CANCELLED") t.cancel();
        tickets.push_back(t);
    }

    in.close();
    std::cout << "State loaded from " << filename << "\n";
}
