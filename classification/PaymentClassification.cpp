#include "PaymentClassification.h"

bool PaymentClassification::IsInPayPeriod(const Date& date, const PayCheck& pc)
{
    Date payPeriodStartDate = pc.GetPayPeriodStartDate();
    Date payPeriodEndDate = pc.GetPayPeriodEndDate();
    return (date > payPeriodStartDate) && (date <= payPeriodEndDate);
}