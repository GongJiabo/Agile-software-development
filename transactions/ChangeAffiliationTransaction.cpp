#include "ChangeAffiliationTransaction.h"

#include "../utility/Employee.h"

ChangeAffiliationTransaction::ChangeAffiliationTransaction(int empid)
    : ChangeEmployeeTransaction(empid)
{
}

void ChangeAffiliationTransaction::Change(Employee& e)
{
    RecordMembership(&e);
    e.SetAffiliation(GetAffiliation());
}
