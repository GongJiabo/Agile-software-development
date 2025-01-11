#pragma once

#include "Date.h"

class SalesReceipt
{
public:
    SalesReceipt(const Date& date, double amount);
    virtual ~SalesReceipt() = default;

    Date GetDate() const { return itsDate; }
    double GetAmount() const { return itsAmount; }

private:
    Date itsDate;
    double itsAmount;
};