#pragma once

#include "ChangeMethodTransaction.h"

class ChangeHoldMethodTransaction : public ChangeMethodTransaction
{
public:
    explicit ChangeHoldMethodTransaction(int empid);
    virtual ~ChangeHoldMethodTransaction() = default;
    
    PaymentMethod* GetMethod() const override;
};
