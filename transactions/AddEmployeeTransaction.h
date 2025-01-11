#pragma once

#include "Transaction.h"
#include <string>

class PaymentClassification;
class PaymentSchedule;

class AddEmployeeTransaction : public Transaction
{
public:
    AddEmployeeTransaction(int empid, std::string name, std::string address);
    virtual ~AddEmployeeTransaction();
    
    virtual PaymentClassification* GetClassification() const = 0;
    virtual PaymentSchedule* GetSchedule() const = 0;
    void Execute() override;

private:
    int itsEmpid;
    std::string itsName;
    std::string itsAddress;
};
