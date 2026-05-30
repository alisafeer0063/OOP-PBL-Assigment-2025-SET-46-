#ifndef AIRLINE_H
#define AIRLINE_H

#include <vector>
#include <map>
#include <memory>
#include <string>

#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"

class Airline {
    std::string airlineName;

    std::vector<std::shared_ptr<Flight>>    flights;
    std::vector<std::shared_ptr<Passenger>> passengers;
    std::vector<Ticket>                     tickets;

    int nextSeatFor(const std::string& flightNumber) const;
    std::string generateTicketID() const;
    int daysUntilDeparture(const std::string& departureDate) const;

public:
    explicit Airline(const std::string& name);

    // flight management
    void addFlight(std::shared_ptr<Flight> flight);
    bool removeFlight(const std::string& flightNumber);
    std::shared_ptr<Flight> findFlight(const std::string& flightNumber) const;
    std::vector<std::shared_ptr<Flight>> searchByRoute(const std::string& origin,
                                                        const std::string& dest) const;
    std::vector<std::shared_ptr<Flight>> searchByDate(const std::string& date) const;
    void listAllFlights() const;

    // passenger management
    void registerPassenger(std::shared_ptr<Passenger> p);
    bool removePassenger(const std::string& passengerID);
    std::shared_ptr<Passenger> findPassenger(const std::string& passengerID) const;
    void viewBookingHistory(const std::string& passengerID) const;
    void listAllPassengers() const;

    // booking
    Ticket bookTicket(const std::string& passengerID, const std::string& flightNumber);

    // cancellation
    double cancelTicket(const std::string& ticketID);

    // reports
    void reportTodaysDepartures(const std::string& today) const;
    void reportOccupancy() const;
    void reportTopRevenueFlights() const;

    // persistence
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
