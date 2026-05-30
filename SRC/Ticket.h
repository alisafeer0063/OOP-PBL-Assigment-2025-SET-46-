#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <iostream>

enum class BookingStatus { CONFIRMED, CANCELLED };

class Ticket {
    std::string ticketID;
    std::string passengerID;
    std::string flightNumber;
    int seatNumber;
    double farePaid;
    BookingStatus status;

public:
    Ticket(const std::string& ticketID, const std::string& passengerID,
           const std::string& flightNumber, int seatNumber, double farePaid);

    std::string getTicketID() const;
    std::string getPassengerID() const;
    std::string getFlightNumber() const;
    int getSeatNumber() const;
    double getFarePaid() const;
    BookingStatus getStatus() const;
    std::string getStatusString() const;

    void cancel();

    bool operator==(const Ticket& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Ticket& t);
};

#endif
