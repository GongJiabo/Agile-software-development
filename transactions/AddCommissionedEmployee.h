#pragma once

#include "AddEmployeeTransaction.h"

class AddCommissionedEmployee : public AddEmployeeTransaction
{
public:
    AddCommissionedEmployee(int empid, const std::string& name,
                            const std::string& address, double salary,
                            double commissionRate);
    virtual ~AddCommissionedEmployee() = default;


    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;
    double GetSalary() const;

private:
    double itsSalary;
    double itsCommissionRate;
};
