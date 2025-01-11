#pragma once

#include "ChangeEmployeeTransaction.h"
#include <string>

class ChangeAddressTransaction : public ChangeEmployeeTransaction
{
public:
    ChangeAddressTransaction(int empid, std::string address);
    virtual ~ChangeAddressTransaction() = default;

    void Change(Employee& e) override;

private:
    std::string itsAddress;
};
