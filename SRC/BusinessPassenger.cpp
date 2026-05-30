#include "BusinessPassenger.h"

BusinessPassenger::BusinessPassenger(const std::string& id, const std::string& nm,
                                     const std::string& em, const std::string& ph)
    : Passenger(id, nm, em, ph) {}

double BusinessPassenger::getRefundPercent(int days) const {
    if (days > 7)  return 0.75;
    if (days >= 3) return 0.40;
    return 0.10;
}

int BusinessPassenger::getBaggageAllowanceKg() const { return 35; }
double BusinessPassenger::getLoyaltyMultiplier() const { return 1.5; }
std::string BusinessPassenger::getPassengerClass() const { return "Business"; }
