#include "Passenger.h"

Passenger::Passenger(const std::string& id, const std::string& nm,
                     const std::string& em, const std::string& ph)
    : passengerID(id), name(nm), email(em), phone(ph), loyaltyPoints(0) {}

std::string Passenger::getPassengerID() const { return passengerID; }
std::string Passenger::getName() const { return name; }
std::string Passenger::getEmail() const { return email; }
std::string Passenger::getPhone() const { return phone; }
int Passenger::getLoyaltyPoints() const { return loyaltyPoints; }

void Passenger::addLoyaltyPoints(int pts) {
    loyaltyPoints += pts;
}

void Passenger::displayDetails() const {
    std::cout << *this << "\n";
}

std::ostream& operator<<(std::ostream& os, const Passenger& p) {
    os << "[" << p.getPassengerClass() << "] ID: " << p.passengerID
       << " | Name: " << p.name
       << " | Email: " << p.email
       << " | Phone: " << p.phone
       << " | Loyalty Pts: " << p.loyaltyPoints
       << " | Baggage: " << p.getBaggageAllowanceKg() << "kg";
    return os;
}
