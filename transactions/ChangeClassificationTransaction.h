#pragma once

#include "ChangeEmployeeTransaction.h"

class PaymentClassification;
class PaymentSchedule;

class ChangeClassificationTransaction : public ChangeEmployeeTransaction
{
public:
    explicit ChangeClassificationTransaction(int empid);
    virtual ~ChangeClassificationTransaction() = default;

    virtual void Change(Employee&);
    virtual PaymentClassification* GetClassification() const = 0;
    virtual PaymentSchedule* GetSchedule() const = 0;
};