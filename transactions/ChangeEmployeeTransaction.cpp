#include "ChangeEmployeeTransaction.h"

#include "../utility/Employee.h"
#include "../utility/PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

ChangeEmployeeTransaction::ChangeEmployeeTransaction(int empid)
    : itsEmpId(empid)
{
}

void ChangeEmployeeTransaction::Execute()
{
    Employee* e = GpayrollDatabase.GetEmployee(itsEmpId);
    if (e != 0) Change(*e);
}
