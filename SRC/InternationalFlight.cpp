#include "InternationalFlight.h"
#include <iostream>
#include <iomanip>

InternationalFlight::InternationalFlight(const std::string& flightNum, const std::string& orig,
                                         const std::string& dest, const std::string& date,
                                         const std::string& time, int seats,
                                         const std::string& ctry, bool visa, double fare)
    : Flight(flightNum, orig, dest, date, time, seats),
      country(ctry), visaRequired(visa), baseFare(fare) {}

double InternationalFlight::calculateBaseFare() const {
    // international flights add a 15% tax; visa-required routes add another 5%
    double fare = baseFare * 1.15;
    if (visaRequired) fare *= 1.05;
    return fare;
}

void InternationalFlight::displayDetails() const {
    std::cout << *this << "\n";
    std::cout << "  Country: " << country
              << " | Visa Required: " << (visaRequired ? "Yes" : "No") << "\n";
}

std::string InternationalFlight::getType() const { return "International"; }

std::string InternationalFlight::extraInfo() const {
    return country + "," + (visaRequired ? "1" : "0");
}

std::string InternationalFlight::getCountry() const { return country; }
bool InternationalFlight::isVisaRequired() const { return visaRequired; }
