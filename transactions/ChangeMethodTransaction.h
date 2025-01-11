#pragma once

#include "ChangeEmployeeTransaction.h"

class PaymentMethod;

class ChangeMethodTransaction : public ChangeEmployeeTransaction
{
public:
    ChangeMethodTransaction(int empid);
    virtual ~ChangeMethodTransaction() = default;

    virtual PaymentMethod* GetMethod() const = 0;
    virtual void Change(Employee&);
};