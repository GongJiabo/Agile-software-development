#include "ChangeDirectMethodTransaction.h"

#include "../paymentmethod/DirectMethod.h"

ChangeDirectMethodTransaction::ChangeDirectMethodTransaction(int empid, std::string bank,
                                                 std::string account)
    : ChangeMethodTransaction(empid), itsBank(bank), itsAccount(account)
{
}

PaymentMethod* ChangeDirectMethodTransaction::GetMethod() const
{
    return new DirectMethod(itsBank, itsAccount);
}
