#include "Ticket.h"
#include <iomanip>

Ticket::Ticket(const std::string& tid, const std::string& pid,
               const std::string& fnum, int seat, double fare)
    : ticketID(tid), passengerID(pid), flightNumber(fnum),
      seatNumber(seat), farePaid(fare), status(BookingStatus::CONFIRMED) {}

std::string Ticket::getTicketID() const { return ticketID; }
std::string Ticket::getPassengerID() const { return passengerID; }
std::string Ticket::getFlightNumber() const { return flightNumber; }
int Ticket::getSeatNumber() const { return seatNumber; }
double Ticket::getFarePaid() const { return farePaid; }
BookingStatus Ticket::getStatus() const { return status; }

std::string Ticket::getStatusString() const {
    return (status == BookingStatus::CONFIRMED) ? "CONFIRMED" : "CANCELLED";
}

void Ticket::cancel() {
    status = BookingStatus::CANCELLED;
}

bool Ticket::operator==(const Ticket& other) const {
    return ticketID == other.ticketID;
}

std::ostream& operator<<(std::ostream& os, const Ticket& t) {
    os << "Ticket ID: " << t.ticketID
       << " | Passenger: " << t.passengerID
       << " | Flight: " << t.flightNumber
       << " | Seat: " << t.seatNumber
       << " | Fare: $" << std::fixed << std::setprecision(2) << t.farePaid
       << " | Status: " << t.getStatusString();
    return os;
}
