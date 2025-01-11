#pragma once

#include "Transaction.h"

class DeleteEmployeeTransaction : public Transaction
{
public:
    explicit DeleteEmployeeTransaction(int empid);
    virtual ~DeleteEmployeeTransaction() = default;
    
    void Execute() override;

private:
    int itsEmpid;
};