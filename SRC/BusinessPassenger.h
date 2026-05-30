#ifndef BUSINESS_PASSENGER_H
#define BUSINESS_PASSENGER_H

#include "Passenger.h"

class BusinessPassenger : public Passenger {
public:
    BusinessPassenger(const std::string& id, const std::string& name,
                      const std::string& email, const std::string& phone);

    // refund: 75% if >7 days, 40% if 3-7 days, 10% otherwise
    double getRefundPercent(int daysBeforeDeparture) const override;
    int getBaggageAllowanceKg() const override;
    double getLoyaltyMultiplier() const override;
    std::string getPassengerClass() const override;
};

#endif
