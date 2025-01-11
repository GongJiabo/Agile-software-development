#include "ChangeMailMethodTransaction.h"

#include "../paymentmethod/MailMethod.h"

ChangeMailMethodTransaction::ChangeMailMethodTransaction(int empid, std::string address)
    : ChangeMethodTransaction(empid), itsAddress(address)
{
}

PaymentMethod* ChangeMailMethodTransaction::GetMethod() const
{
    return new MailMethod(itsAddress);
}
