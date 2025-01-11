#include "AddCommissionedEmployee.h"

#include "../classification/CommissionedClassification.h"
#include "../schedule/BiweeklySchedule.h"

AddCommissionedEmployee::AddCommissionedEmployee(int empid,
                                                 const std::string& name,
                                                 const std::string& address,
                                                 double salary,
                                                 double commissionRate)
    : AddEmployeeTransaction(empid, name, address),
      itsSalary(salary),
      itsCommissionRate(commissionRate)
{
}

PaymentClassification* AddCommissionedEmployee::GetClassification() const
{
    return new CommissionedClassification(itsSalary, itsCommissionRate);
}

PaymentSchedule* AddCommissionedEmployee::GetSchedule() const
{
    return new BiweeklySchedule();
}

double AddCommissionedEmployee::GetSalary() const
{
    return itsSalary;
}
