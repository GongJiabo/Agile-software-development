#pragma once

#include "PaymentClassification.h"
#include "../utility/PayCheck.h"

class SalariedClassification : public PaymentClassification
{
public:
    explicit SalariedClassification(double salary);
    virtual ~SalariedClassification() = default;

    double GetSalary() const;
    double CalculatePay(const PayCheck& pc) override;

private:
    double itsSalary;
};