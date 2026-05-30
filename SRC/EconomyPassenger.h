#ifndef ECONOMY_PASSENGER_H
#define ECONOMY_PASSENGER_H

#include "Passenger.h"

class EconomyPassenger : public Passenger {
public:
    EconomyPassenger(const std::string& id, const std::string& name,
                     const std::string& email, const std::string& phone);

    // refund: 50% if >7 days before, 20% if 3-7 days, 0% otherwise
    double getRefundPercent(int daysBeforeDeparture) const override;
    int getBaggageAllowanceKg() const override;
    double getLoyaltyMultiplier() const override;
    std::string getPassengerClass() const override;
};

#endif
