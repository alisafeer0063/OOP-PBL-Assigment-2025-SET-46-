#ifndef CHARTER_FLIGHT_H
#define CHARTER_FLIGHT_H

#include "Flight.h"

class CharterFlight : public Flight {
    std::string contractHolder;
    double contractPrice;  // total price for the charter

public:
    CharterFlight(const std::string& flightNum, const std::string& orig,
                  const std::string& dest, const std::string& date,
                  const std::string& time, int seats,
                  const std::string& holder, double price);

    double calculateBaseFare() const override;
    void displayDetails() const override;
    std::string getType() const override;
    std::string extraInfo() const override;

    std::string getContractHolder() const;
    double getContractPrice() const;
};

#endif
