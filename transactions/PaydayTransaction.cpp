#include "PaydayTransaction.h"

#include <list>
#include "../utility/PayrollDatabase.h"
#include "../utility/Employee.h"

extern PayrollDatabase GpayrollDatabase;

PaydayTransaction::PaydayTransaction(Date payDate) : itsPayDate(payDate) {}

void PaydayTransaction::Execute()
{
    std::list<int> empIds;
    GpayrollDatabase.GetAllEmployeeIds(empIds);

    std::list<int>::iterator i = empIds.begin();
    for (; i != empIds.end(); i++)
    {
        int empId = *i;
        if (Employee* e = GpayrollDatabase.GetEmployee(empId))
        {
            if (e->IsPayDate(itsPayDate))
            {
                PayCheck* pc = new PayCheck(
                    e->GetPayPeriodStartDate(itsPayDate), itsPayDate);
                itsPaychecks[empId] = pc;
                e->Payday(*pc);
            }
        }
    }
}

PayCheck* PaydayTransaction::GetPaycheck(int empId)
{
    return itsPaychecks[empId];
}

int PaydayTransaction::GetPaycheckCount() const { return itsPaychecks.size(); }
