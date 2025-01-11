#pragma once

#include "AddEmployeeTransaction.h"

class AddSalariedEmployee : public AddEmployeeTransaction
{
public:
    AddSalariedEmployee(int empid, const std::string& name,
                        const std::string& address, double salary);
    virtual ~AddSalariedEmployee() = default;

    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;

private:
    double itsSalary;
};
