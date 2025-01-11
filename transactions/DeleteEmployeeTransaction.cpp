#include "DeleteEmployeeTransaction.h"

#include "../utility/PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

DeleteEmployeeTransaction::DeleteEmployeeTransaction(int empid)
    : itsEmpid(empid)
{
}

void DeleteEmployeeTransaction::Execute()
{
    GpayrollDatabase.DeleteEmployee(itsEmpid);
}
