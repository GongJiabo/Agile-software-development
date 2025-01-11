#include "BiweeklySchedule.h"

bool BiweeklySchedule::IsPayDate(const Date& payDate)
{
    Date first_pay_date(3, 31, 2017);
    auto duration = payDate - first_pay_date;

    if (duration % 14 == 0)
        return true;
    else
        return false;
}

Date BiweeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate)
{
    return payPeriodEndDate - 13;
}
