#pragma once

#include "ChangeClassificationTransaction.h"

class ChangeHourlyTransaction : public ChangeClassificationTransaction
{
public:
    ChangeHourlyTransaction(int empid, double hourlyRate);
    virtual ~ChangeHourlyTransaction() = default;
    
    PaymentSchedule* GetSchedule() const override;
    PaymentClassification* GetClassification() const override;

private:
    double itsHourlyRate;
};