#pragma once

#include "../utility/Date.h"

class PaymentSchedule
{
public:
    PaymentSchedule() = default;
    virtual ~PaymentSchedule() = default;

    virtual bool IsPayDate(const Date& payDate) = 0;
    virtual Date GetPayPeriodStartDate(const Date& payPeriodEndDate) = 0;
};
