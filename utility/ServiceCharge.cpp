#include "ServiceCharge.h"

ServiceCharge::ServiceCharge(const Date& date, double charge)
    : itsDate(date), itsCharge(charge)
{
}

double ServiceCharge::GetAmount() const { return itsCharge; }

Date ServiceCharge::GetServiceDate() const { return itsDate; }
