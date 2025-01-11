#include "SalariedClassification.h"

SalariedClassification::SalariedClassification(double salary)
    : itsSalary(salary)
{
}

double SalariedClassification::GetSalary() const { return itsSalary; }

double SalariedClassification::CalculatePay(const PayCheck& pc)
{
    return itsSalary;
}
