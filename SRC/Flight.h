#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <iostream>

class Flight {
protected:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureDate;  // format: YYYY-MM-DD
    std::string departureTime;  // format: HH:MM
    int totalSeats;
    int availableSeats;

public:
    Flight(const std::string& flightNum, const std::string& orig,
           const std::string& dest, const std::string& date,
           const std::string& time, int seats);

    virtual ~Flight() = default;

    // pure virtual functions
    virtual double calculateBaseFare() const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string extraInfo() const = 0;

    // getters
    std::string getFlightNumber() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::string getDepartureDate() const;
    std::string getDepartureTime() const;
    int getTotalSeats() const;
    int getAvailableSeats() const;

    // seat operations
    bool bookSeat();
    void releaseSeat();

    double getOccupancyPercent() const;

    // operator overload
    friend std::ostream& operator<<(std::ostream& os, const Flight& f);

    bool operator==(const Flight& other) const;
};

#endif
