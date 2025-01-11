#include "AddSalariedEmployee.h"

#include "../classification/SalariedClassification.h"
#include "../schedule/MonthlySchedule.h"

AddSalariedEmployee::AddSalariedEmployee(int empid, const std::string& name,
                                         const std::string& address,
                                         double salary)
    : AddEmployeeTransaction(empid, name, address), itsSalary(salary)
{
}

PaymentClassification* AddSalariedEmployee::GetClassification() const
{
    return new SalariedClassification(itsSalary);
}

PaymentSchedule* AddSalariedEmployee::GetSchedule() const
{
    return new MonthlySchedule();
}