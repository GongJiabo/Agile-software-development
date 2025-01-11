#include "HourlyClassification.h"

HourlyClassification::HourlyClassification(double hourlyRate)
    : itsHourlyRate(hourlyRate)
{
}

double HourlyClassification::CalculatePay(const PayCheck& pc)
{
    double totalPay = 0;
    Date payPeriodEndDate = pc.GetPayPeriodEndDate();
    std::map<Date, TimeCard*>::const_iterator i;
    for (i = itsTimeCards.begin(); i != itsTimeCards.end(); i++)
    {
        TimeCard* tc = (*i).second;
        if (IsInPayPeriod(tc->GetDate(), pc))
            totalPay += CalculatePayForTimeCard(tc);
    }
    return totalPay;
}

TimeCard* HourlyClassification::GetTimeCard(const Date& date)
{
    if (itsTimeCards.find(date) != itsTimeCards.end())
    {
        return itsTimeCards[date];
    }
    return nullptr;
}

void HourlyClassification::AddTimeCard(const Date& date, TimeCard* timeCard)
{
    itsTimeCards[date] = timeCard;
}

double HourlyClassification::GetHourlyRate() const { return itsHourlyRate; }

double HourlyClassification::CalculatePayForTimeCard(TimeCard* tc) const
{
    double hours = tc->GetHours();
    double overtime = std::max(0.0, hours - 8.0);
    double straightTime = hours - overtime;
    return straightTime * itsHourlyRate + overtime * itsHourlyRate * 1.5;
}