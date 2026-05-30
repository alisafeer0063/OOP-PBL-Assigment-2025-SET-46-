#ifndef DOMESTIC_FLIGHT_H
#define DOMESTIC_FLIGHT_H

#include "Flight.h"

class DomesticFlight : public Flight {
    std::string region;  // e.g., "North", "South"
    double baseFare;

public:
    DomesticFlight(const std::string& flightNum, const std::string& orig,
                   const std::string& dest, const std::string& date,
                   const std::string& time, int seats,
                   const std::string& region, double fare);

    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;
    std::string extraInfo() const override;

    std::string getRegion() const;
};

#endif
