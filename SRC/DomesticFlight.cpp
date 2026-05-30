#include "DomesticFlight.h"
#include <iostream>
#include <iomanip>

DomesticFlight::DomesticFlight(const std::string& flightNum, const std::string& orig,
                               const std::string& dest, const std::string& date,
                               const std::string& time, int seats,
                               const std::string& reg, double fare)
    : Flight(flightNum, orig, dest, date, time, seats), region(reg), baseFare(fare) {}

double DomesticFlight::calculateBaseFare() const {
    // domestic flights have a flat fare with small regional surcharge
    double surcharge = (region == "North" || region == "South") ? 1.05 : 1.0;
    return baseFare * surcharge;
}

void DomesticFlight::displayDetails() const {
    std::cout << *this << "\n";
    std::cout << "  Region: " << region << "\n";
}

std::string DomesticFlight::getType() const { return "Domestic"; }

std::string DomesticFlight::extraInfo() const { return region; }

std::string DomesticFlight::getRegion() const { return region; }
