#include "TimeCardTransaction.h"

#include "../classification/HourlyClassification.h"
#include "../utility/Employee.h"
#include "../utility/PayrollDatabase.h"
#include "../utility/TimeCard.h"

extern PayrollDatabase GpayrollDatabase;

TimeCardTransaction::TimeCardTransaction(const Date& date, double hours,
                                         int empid)
    : itsDate(date), itsHours(hours), itsEmpid(empid)
{
}

void TimeCardTransaction::Execute()
{
    Employee* e = GpayrollDatabase.GetEmployee(itsEmpid);
    if (e)
    {
        PaymentClassification* pc = e->GetClassification();
        if (HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc))
        {
            hc->AddTimeCard(itsDate, new TimeCard(itsDate, itsHours));
        }
        else
            throw("Tried to add timecard to non-hourly employee");
    }
    else
        throw("No such employee.");
}
