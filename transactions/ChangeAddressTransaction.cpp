#include "ChangeAddressTransaction.h"

#include "../utility/Employee.h"

ChangeAddressTransaction::ChangeAddressTransaction(int empid,
                                                   std::string address)
    : ChangeEmployeeTransaction(empid), itsAddress(address)
{
}

void ChangeAddressTransaction::Change(Employee& e) { e.SetAddress(itsAddress); }
