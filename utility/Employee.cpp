#include "Employee.h"

#include "../utility/PayCheck.h"
#include "../affiliation/NoAffiliation.h"
#include "../classification/PaymentClassification.h"
#include "../paymentmethod/PaymentMethod.h"
#include "../schedule/PaymentSchedule.h"

Employee::Employee(int empid, std::string name, std::string address)
    : itsEmpid(empid),
      itsName(name),
      itsAddress(address),
      itsAffiliation(new NoAffiliation()),
      itsClassification(nullptr),
      itsSchedule(nullptr),
      itsPaymentMethod(nullptr)
{
}

void Employee::SetName(std::string name) { itsName = name; }

void Employee::SetAddress(std::string address) { itsAddress = address; }

void Employee::SetClassification(PaymentClassification* pc)
{
    delete itsClassification;
    itsClassification = pc;
}

void Employee::SetSchedule(PaymentSchedule* ps)
{
    delete itsSchedule;
    itsSchedule = ps;
}

void Employee::SetMethod(PaymentMethod* pm)
{
    delete itsPaymentMethod;
    itsPaymentMethod = pm;
}

void Employee::SetAffiliation(Affiliation* af)
{
    delete itsAffiliation;
    itsAffiliation = af;
}

void Employee::Payday(PayCheck& pc)
{
    double grossPay = itsClassification->CalculatePay(pc);
    double deductions = itsAffiliation->CalculateDeductions(pc);
    double netPay = grossPay - deductions;
    pc.SetGrossPay(grossPay);
    pc.SetDeductions(deductions);
    pc.SetNetPay(netPay);
    itsPaymentMethod->Pay(pc);
}

bool Employee::IsPayDate(const Date& payDate) const
{
    return itsSchedule->IsPayDate(payDate);
}

Date Employee::GetPayPeriodStartDate(const Date& payPeriodEndDate) const
{
    return itsSchedule->GetPayPeriodStartDate(payPeriodEndDate);
}
