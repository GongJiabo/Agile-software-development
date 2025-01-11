#include "UnionAffiliation.h"

UnionAffiliation::UnionAffiliation(int id) : itsUnionId(id) {}

UnionAffiliation::UnionAffiliation(int id, double dues)
    : itsUnionId(id), itsDues(dues)
{
}

double UnionAffiliation::CalculateDeductions(const PayCheck& payCheck)
{
    double totalDues = 0;
    int fridays = NumberOfFridaysInpayPeriod(payCheck.GetPayPeriodStartDate(),
                                             payCheck.GetPayPeriodEndDate());
    totalDues = itsDues * fridays;

    for (auto it = itsServiceCharges.begin(); it != itsServiceCharges.end();
         ++it)
    {
        if (it->first >= payCheck.GetPayPeriodStartDate() && it->first <= payCheck.GetPayPeriodEndDate())
        {
            totalDues += it->second->GetAmount();
        }
    }

    return totalDues;
}

ServiceCharge* UnionAffiliation::GetServiceCharge(const Date& date) const
{
    if (itsServiceCharges.find(date) == itsServiceCharges.end()) {
        return nullptr;
    }
    return itsServiceCharges.at(date);
}

void UnionAffiliation::AddServiceCharge(const Date& date, double charge)
{
    itsServiceCharges[date] = new ServiceCharge(date, charge);
}

int UnionAffiliation::NumberOfFridaysInpayPeriod(const Date& payPeriodStart,
                                                 const Date& payPeriodEnd)
{
    int fridays = 0;
    for (Date day = payPeriodStart; day <= payPeriodEnd; ++day)
    {
        if (day.GetDayOfWeek() == Date::friday)
        {
            ++fridays;
        }
    }
    return fridays;
}
