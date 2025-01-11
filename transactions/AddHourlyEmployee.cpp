#include "AddHourlyEmployee.h"

#include "../classification/HourlyClassification.h"
#include "../schedule/WeeklySchedule.h"

AddHourlyEmployee::AddHourlyEmployee(int empid, const std::string& name,
                                     const std::string& address,
                                     double hourlyRate)
    : AddEmployeeTransaction(empid, name, address), itsHourlyRate(hourlyRate)
{
}

PaymentClassification* AddHourlyEmployee::GetClassification() const
{
    return new HourlyClassification(itsHourlyRate);
}

PaymentSchedule* AddHourlyEmployee::GetSchedule() const
{
    return new WeeklySchedule();
}

double AddHourlyEmployee::getHourlyRate() const { return itsHourlyRate; }
