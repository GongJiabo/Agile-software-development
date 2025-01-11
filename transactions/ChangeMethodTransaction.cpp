#include "ChangeMethodTransaction.h"

ChangeMethodTransaction::ChangeMethodTransaction(int empid)
    : ChangeEmployeeTransaction(empid)
{
}

void ChangeMethodTransaction::Change(Employee& e) { e.SetMethod(GetMethod()); }
