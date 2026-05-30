#include "CharterFlight.h"
#include <iostream>
#include <iomanip>

CharterFlight::CharterFlight(const std::string& flightNum, const std::string& orig,
                             const std::string& dest, const std::string& date,
                             const std::string& time, int seats,
                             const std::string& holder, double price)
    : Flight(flightNum, orig, dest, date, time, seats),
      contractHolder(holder), contractPrice(price) {}

double CharterFlight::calculateBaseFare() const {
    // per-seat fare = total contract price divided by total seats
    if (totalSeats == 0) return 0.0;
    return contractPrice / totalSeats;
}

void CharterFlight::displayDetails() const {
    std::cout << *this << "\n";
    std::cout << "  Contract Holder: " << contractHolder
              << " | Total Contract: $" << std::fixed << std::setprecision(2) << contractPrice << "\n";
}

std::string CharterFlight::getType() const { return "Charter"; }

std::string CharterFlight::extraInfo() const {
    return contractHolder;
}

std::string CharterFlight::getContractHolder() const { return contractHolder; }
double CharterFlight::getContractPrice() const { return contractPrice; }
