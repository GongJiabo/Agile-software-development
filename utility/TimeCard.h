#pragma once

#include "Date.h"

class TimeCard
{
public:
    TimeCard(const Date& date, double hours);
    virtual ~TimeCard() = default;

    Date GetDate() const { return itsDate; }
    double GetHours() const { return itsHours; }

private:
    Date itsDate;
    double itsHours;
};