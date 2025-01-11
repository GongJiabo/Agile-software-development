#pragma once

#include "../utility/Date.h"
#include "../utility/PayCheck.h"

class PaymentClassification
{
public:
    PaymentClassification() = default;
    virtual ~PaymentClassification() = default;

    virtual double CalculatePay(const PayCheck& pc) = 0;
    bool IsInPayPeriod(const Date& date, const PayCheck& pc);
};