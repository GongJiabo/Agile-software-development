#pragma once

#include "../utility/PayCheck.h"

class PaymentMethod
{
public:
    PaymentMethod() = default;
    virtual ~PaymentMethod() = default;

    virtual void Pay(PayCheck& payCheck) = 0;
};