#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <iostream>

class Passenger {
protected:
    std::string passengerID;
    std::string name;
    std::string email;
    std::string phone;
    int loyaltyPoints;

public:
    Passenger(const std::string& id, const std::string& name,
              const std::string& email, const std::string& phone);

    virtual ~Passenger() = default;

    virtual double getRefundPercent(int daysBeforeDeparture) const = 0;
    virtual int getBaggageAllowanceKg() const = 0;
    virtual double getLoyaltyMultiplier() const = 0;
    virtual std::string getPassengerClass() const = 0;
    virtual void displayDetails() const;

    std::string getPassengerID() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    int getLoyaltyPoints() const;

    void addLoyaltyPoints(int pts);

    friend std::ostream& operator<<(std::ostream& os, const Passenger& p);
};

#endif
