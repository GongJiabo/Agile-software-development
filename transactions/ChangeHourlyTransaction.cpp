#include "ChangeHourlyTransaction.h"

#include "../classification/HourlyClassification.h"
#include "../schedule/WeeklySchedule.h"

ChangeHourlyTransaction::ChangeHourlyTransaction(int empid, double hourlyRate)
    : ChangeClassificationTransaction(empid), itsHourlyRate(hourlyRate)
{
}

PaymentSchedule* ChangeHourlyTransaction::GetSchedule() const
{
    return new WeeklySchedule();
}

PaymentClassification* ChangeHourlyTransaction::GetClassification() const
{
    return new HourlyClassification(itsHourlyRate);
}
