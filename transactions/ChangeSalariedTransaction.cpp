#include "ChangeSalariedTransaction.h"

#include "../schedule/MonthlySchedule.h"
#include "../classification/SalariedClassification.h"

ChangeSalariedTransaction::ChangeSalariedTransaction(int empid, double salary)
    : ChangeClassificationTransaction(empid), itsSalary(salary)
{
}

PaymentSchedule* ChangeSalariedTransaction::GetSchedule() const
{
    return new MonthlySchedule();
}

PaymentClassification* ChangeSalariedTransaction::GetClassification() const
{
    return new SalariedClassification(itsSalary);
}
