#include "Flight.h"
#include <iomanip>

Flight::Flight(const std::string& flightNum, const std::string& orig,
               const std::string& dest, const std::string& date,
               const std::string& time, int seats)
    : flightNumber(flightNum), origin(orig), destination(dest),
      departureDate(date), departureTime(time),
      totalSeats(seats), availableSeats(seats) {}

std::string Flight::getFlightNumber() const { return flightNumber; }
std::string Flight::getOrigin() const { return origin; }
std::string Flight::getDestination() const { return destination; }
std::string Flight::getDepartureDate() const { return departureDate; }
std::string Flight::getDepartureTime() const { return departureTime; }
int Flight::getTotalSeats() const { return totalSeats; }
int Flight::getAvailableSeats() const { return availableSeats; }

bool Flight::bookSeat() {
    if (availableSeats <= 0) return false;
    availableSeats--;
    return true;
}

void Flight::releaseSeat() {
    if (availableSeats < totalSeats)
        availableSeats++;
}

double Flight::getOccupancyPercent() const {
    if (totalSeats == 0) return 0.0;
    return ((double)(totalSeats - availableSeats) / totalSeats) * 100.0;
}

bool Flight::operator==(const Flight& other) const {
    return flightNumber == other.flightNumber;
}

std::ostream& operator<<(std::ostream& os, const Flight& f) {
    os << "[" << f.getType() << "] Flight: " << f.flightNumber
       << " | " << f.origin << " -> " << f.destination
       << " | Date: " << f.departureDate << " " << f.departureTime
       << " | Seats: " << f.availableSeats << "/" << f.totalSeats
       << " | Base Fare: $" << std::fixed << std::setprecision(2) << f.calculateBaseFare();
    return os;
}
