#pragma once

#include "PaymentSchedule.h"
#include "../utility/Date.h"

class MonthlySchedule : public PaymentSchedule
{
public:
    MonthlySchedule() = default;
    virtual ~MonthlySchedule() = default;

    bool IsPayDate(const Date& payDate) override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) override;
};
