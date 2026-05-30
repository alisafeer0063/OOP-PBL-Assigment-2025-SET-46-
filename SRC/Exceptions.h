#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class FlightFullException : public std::exception {
    std::string msg;
public:
    explicit FlightFullException(const std::string& flightNum)
        : msg("Flight " + flightNum + " is fully booked.") {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class InvalidCancellationException : public std::exception {
    std::string msg;
public:
    explicit InvalidCancellationException(const std::string& reason)
        : msg("Cancellation error: " + reason) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class DuplicateBookingException : public std::exception {
    std::string msg;
public:
    explicit DuplicateBookingException(const std::string& passengerID, const std::string& flightNum)
        : msg("Passenger " + passengerID + " already has a ticket on flight " + flightNum + ".") {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class NotFoundException : public std::exception {
    std::string msg;
public:
    explicit NotFoundException(const std::string& detail)
        : msg("Not found: " + detail) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

#endif
