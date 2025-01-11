#pragma once

#include "Transaction.h"
#include "../utility/Date.h"

class TimeCardTransaction : public Transaction
{
public:
    TimeCardTransaction(const Date& date, double hours, int empid);
    virtual ~TimeCardTransaction() = default;

    void Execute() override;

private:
    int itsEmpid;
    Date itsDate;
    double itsHours;
};
