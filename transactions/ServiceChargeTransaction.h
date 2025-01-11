#pragma once

#include "Transaction.h"
#include "../utility/Date.h"

class ServiceChargeTransaction : public Transaction
{
public:
    ServiceChargeTransaction(int memberId, const Date& date, double charge);
    virtual ~ServiceChargeTransaction() = default;
    
    void Execute() override;

private:
    int itsMemberId;
    Date itsDate;
    double itsCharge;
};
