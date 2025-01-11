#include "SalesReceiptTransaction.h"

#include "../classification/CommissionedClassification.h"
#include "../utility/Employee.h"
#include "../utility/PayrollDatabase.h"
#include "../utility/SalesReceipt.h"

extern PayrollDatabase GpayrollDatabase;

SalesReceiptTransaction::SalesReceiptTransaction(const Date& saleDate,
                                                 double amount, int empid)
    : itsSaleDate(saleDate), itsAmount(amount), itsEmpid(empid)
{
}

void SalesReceiptTransaction::Execute()
{
    Employee* e = GpayrollDatabase.GetEmployee(itsEmpid);
    if (e)
    {
        PaymentClassification* pc = e->GetClassification();
        if (CommissionedClassification* cc =
                dynamic_cast<CommissionedClassification*>(pc))
        {
            cc->AddSalesReceipt(new SalesReceipt(itsSaleDate, itsAmount));
        }
        else
            throw("Tried to add sales receipt to non-commissioned employee");
    }
    else
        throw("No such employee.");
}
