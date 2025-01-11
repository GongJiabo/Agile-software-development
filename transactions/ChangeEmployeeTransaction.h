
#pragma once

#include "Transaction.h"
#include "../utility/Employee.h"

class ChangeEmployeeTransaction : public Transaction
{
public:
    ChangeEmployeeTransaction(int empid);
    virtual ~ChangeEmployeeTransaction() = default;

    virtual void Execute();
    virtual void Change(Employee &) = 0;

protected:
    int GetEmpId() { return itsEmpId; }

private:
    int itsEmpId;
};
