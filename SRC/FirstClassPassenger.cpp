#include "FirstClassPassenger.h"

FirstClassPassenger::FirstClassPassenger(const std::string& id, const std::string& nm,
                                         const std::string& em, const std::string& ph)
    : Passenger(id, nm, em, ph) {}

double FirstClassPassenger::getRefundPercent(int days) const {
    if (days > 7)  return 0.90;
    if (days >= 3) return 0.60;
    return 0.25;
}

int FirstClassPassenger::getBaggageAllowanceKg() const { return 50; }
double FirstClassPassenger::getLoyaltyMultiplier() const { return 2.0; }
std::string FirstClassPassenger::getPassengerClass() const { return "FirstClass"; }
