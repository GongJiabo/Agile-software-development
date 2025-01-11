#pragma once

#include "PaymentSchedule.h"
#include "../utility/Date.h"

class WeeklySchedule : public PaymentSchedule
{
public:
    WeeklySchedule() = default;
    virtual ~WeeklySchedule() = default;

    bool IsPayDate(const Date& payDate) override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) override;
};
