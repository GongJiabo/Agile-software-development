#pragma once

#include "Transaction.h"
#include "../utility/Date.h"

class SalesReceiptTransaction : public Transaction
{
public:
    SalesReceiptTransaction(const Date& saleDate, double amount, int empid);
    virtual ~SalesReceiptTransaction() = default;

    void Execute() override;

private:
    int itsEmpid;
    Date itsSaleDate;
    double itsAmount;
};