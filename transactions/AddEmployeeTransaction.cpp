#include "AddEmployeeTransaction.h"

#include "../classification/PaymentClassification.h"
#include "../paymentmethod/HoldMethod.h"
#include "../utility/Employee.h"
#include "../utility/PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

AddEmployeeTransaction::~AddEmployeeTransaction() {}

AddEmployeeTransaction::AddEmployeeTransaction(int empid, std::string name,
                                               std::string address)
    : itsEmpid(empid), itsName(name), itsAddress(address)
{
}

void AddEmployeeTransaction::Execute()
{
    PaymentClassification* pc = GetClassification();
    PaymentSchedule* ps = GetSchedule();
    PaymentMethod* pm = new HoldMethod();
    Employee* e = new Employee(itsEmpid, itsName, itsAddress);
    e->SetClassification(pc);
    e->SetSchedule(ps);
    e->SetMethod(pm);
    GpayrollDatabase.AddEmployee(itsEmpid, e);
}
