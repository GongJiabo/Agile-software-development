#pragma once

#include "PaymentMethod.h"

class HoldMethod : public PaymentMethod
{
public:
    HoldMethod() = default;
    ~HoldMethod() = default;

    void Pay(PayCheck& payCheck) override;
};