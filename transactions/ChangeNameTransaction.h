#pragma once

#include <string>
#include "ChangeEmployeeTransaction.h"

class ChangeNameTransaction : public ChangeEmployeeTransaction
{
public:
    ChangeNameTransaction(int empid, std::string name);
    virtual ~ChangeNameTransaction() = default;

    void Change(Employee &) override;

private:
    std::string itsName;
};
