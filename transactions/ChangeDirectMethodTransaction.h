#pragma once

#include "ChangeMethodTransaction.h"
#include <string>

class ChangeDirectMethodTransaction : public ChangeMethodTransaction
{
public:
    ChangeDirectMethodTransaction(int empid, std::string bank, std::string account);
    virtual ~ChangeDirectMethodTransaction() = default;

    virtual PaymentMethod* GetMethod() const;

private:
    std::string itsBank;
    std::string itsAccount;
};
