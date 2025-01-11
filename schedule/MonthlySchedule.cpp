#include "MonthlySchedule.h"

bool MonthlySchedule::IsPayDate(const Date& payDate)
{
    return Date::IsLastDayOfMonth(payDate);
}

Date MonthlySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate)
{
    return Date(payPeriodEndDate.GetMonth(), 1, payPeriodEndDate.GetYear());
}
