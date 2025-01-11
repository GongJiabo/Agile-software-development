#include "WeeklySchedule.h"

bool WeeklySchedule::IsPayDate(const Date& payDate)
{
    return payDate.GetDayOfWeek() == Date::friday;
}

Date WeeklySchedule::GetPayPeriodStartDate(const Date& payPeriodEndDate)
{
    return payPeriodEndDate - 4;
}
