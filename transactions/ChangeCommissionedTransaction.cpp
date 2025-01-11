#include "ChangeCommissionedTransaction.h"

#include "../schedule/BiweeklySchedule.h"
#include "../classification/CommissionedClassification.h"

ChangeCommissionedTransaction::ChangeCommissionedTransaction(int empid,
                                                             double salary,
                                                             double rate)
    : ChangeClassificationTransaction(empid), itsSalary(salary), itsRate(rate)
{
}

PaymentSchedule* ChangeCommissionedTransaction::GetSchedule() const
{
    return new BiweeklySchedule();
}

PaymentClassification* ChangeCommissionedTransaction::GetClassification() const
{
    return new CommissionedClassification(itsSalary, itsRate);
}
