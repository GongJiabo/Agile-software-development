#pragma once

#include "ChangeClassificationTransaction.h"

class ChangeCommissionedTransaction : public ChangeClassificationTransaction
{
public:
    ChangeCommissionedTransaction(int empid, double salary, double rate);
    virtual ~ChangeCommissionedTransaction() = default;

    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsSalary;
    double itsRate;
};