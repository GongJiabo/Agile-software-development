#pragma once

#include "Date.h"

class ServiceCharge
{
public:
    ServiceCharge(const Date& date, double charge);
    virtual ~ServiceCharge() = default;

    double GetAmount() const;
    Date GetServiceDate() const;

private:
    Date itsDate;
    double itsCharge;
};
