#ifndef FIRST_CLASS_PASSENGER_H
#define FIRST_CLASS_PASSENGER_H

#include "Passenger.h"

class FirstClassPassenger : public Passenger {
public:
    FirstClassPassenger(const std::string& id, const std::string& name,
                        const std::string& email, const std::string& phone);

    // refund: 90% if >7 days, 60% if 3-7 days, 25% otherwise
    double getRefundPercent(int daysBeforeDeparture) const override;
    int getBaggageAllowanceKg() const override;
    double getLoyaltyMultiplier() const override;
    std::string getPassengerClass() const override;
};

#endif
