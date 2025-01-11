#pragma once

#include "PaymentSchedule.h"
#include "../utility/Date.h"

class BiweeklySchedule : public PaymentSchedule
{
public:
    BiweeklySchedule() = default;
    virtual ~BiweeklySchedule() = default;

    bool IsPayDate(const Date& payDate) override;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) override;

private:
    bool isPayWeek = false;
};