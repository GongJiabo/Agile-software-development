#pragma once

#include "ChangeMethodTransaction.h"
#include <string>

class ChangeMailMethodTransaction : public ChangeMethodTransaction
{
public:
    ChangeMailMethodTransaction(int empid, std::string address);
    virtual ~ChangeMailMethodTransaction() = default;

    PaymentMethod* GetMethod() const override;

private:
    std::string itsAddress;
};
