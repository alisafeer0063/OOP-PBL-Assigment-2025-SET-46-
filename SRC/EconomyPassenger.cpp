#include "EconomyPassenger.h"

EconomyPassenger::EconomyPassenger(const std::string& id, const std::string& nm,
                                   const std::string& em, const std::string& ph)
    : Passenger(id, nm, em, ph) {}

double EconomyPassenger::getRefundPercent(int days) const {
    if (days > 7)  return 0.50;
    if (days >= 3) return 0.20;
    return 0.0;
}

int EconomyPassenger::getBaggageAllowanceKg() const { return 20; }
double EconomyPassenger::getLoyaltyMultiplier() const { return 1.0; }
std::string EconomyPassenger::getPassengerClass() const { return "Economy"; }
