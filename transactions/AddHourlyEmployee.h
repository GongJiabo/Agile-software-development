#pragma once

#include "AddEmployeeTransaction.h"

class AddHourlyEmployee : public AddEmployeeTransaction
{
public:
    AddHourlyEmployee(int empid, const std::string& name,
                      const std::string& address, double hourlyRate);
    virtual ~AddHourlyEmployee() = default;

    PaymentClassification* GetClassification() const override;
    PaymentSchedule* GetSchedule() const override;
    double getHourlyRate() const;

private:
    double itsHourlyRate;
};
