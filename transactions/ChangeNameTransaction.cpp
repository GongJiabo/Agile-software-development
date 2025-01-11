#include "ChangeNameTransaction.h"

ChangeNameTransaction::ChangeNameTransaction(int empid, std::string name)
    : ChangeEmployeeTransaction(empid), itsName(name)
{
}

void ChangeNameTransaction::Change(Employee& e) { e.SetName(itsName); }
