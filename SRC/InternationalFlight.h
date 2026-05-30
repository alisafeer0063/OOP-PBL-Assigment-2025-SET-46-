#ifndef INTERNATIONAL_FLIGHT_H
#define INTERNATIONAL_FLIGHT_H

#include "Flight.h"

class InternationalFlight : public Flight {
    std::string country;
    bool visaRequired;
    double baseFare;

public:
    InternationalFlight(const std::string& flightNum, const std::string& orig,
                        const std::string& dest, const std::string& date,
                        const std::string& time, int seats,
                        const std::string& country, bool visaRequired, double fare);

    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;
    std::string extraInfo() const override;

    std::string getCountry() const;
    bool isVisaRequired() const;
};

#endif
