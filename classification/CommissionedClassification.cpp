#include "CommissionedClassification.h"

CommissionedClassification::CommissionedClassification(double salary,
                                                       double commissionRate)
    : itsSalary(salary), itsCommissionRate(commissionRate)
{
}

void CommissionedClassification::AddSalesReceipt(SalesReceipt* salesReceipt)
{
    itsSalesReceipt.push_back(salesReceipt);
}

SalesReceipt* CommissionedClassification::GetSalesReceipt(
    const Date& date) const
{
    for (const auto& salesReceipt : itsSalesReceipt)
    {
        if (salesReceipt->GetDate() == date)
        {
            return salesReceipt;
        }
    }
    return nullptr;
}

double CommissionedClassification::GetCommissionRate() const
{
    return itsCommissionRate;
}

double CommissionedClassification::GetSalary() const
{
    return itsSalary;
}

double CommissionedClassification::CalculatePay(const PayCheck& pc)
{
    double total = 0;
    for (const auto& salesReceipt : itsSalesReceipt)
    {
        if (IsInPayPeriod(salesReceipt->GetDate(), pc))
        {
            total += salesReceipt->GetAmount();
        }
    }
    return total * itsCommissionRate + itsSalary;
}