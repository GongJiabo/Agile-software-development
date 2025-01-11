#pragma once

#include "ChangeClassificationTransaction.h"

class ChangeSalariedTransaction : public ChangeClassificationTransaction
{
public:
    ChangeSalariedTransaction(int empid, double salary);
    virtual ~ChangeSalariedTransaction() = default;

    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
};
