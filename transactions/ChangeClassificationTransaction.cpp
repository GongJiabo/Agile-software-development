#include "ChangeClassificationTransaction.h"

#include "../utility/Employee.h"

ChangeClassificationTransaction::ChangeClassificationTransaction(int empid)
    : ChangeEmployeeTransaction(empid)
{
}

void ChangeClassificationTransaction::Change(Employee& e)
{
    e.SetClassification(GetClassification());
    e.SetSchedule(GetSchedule());
}
