#include "ChangeHoldMethodTransaction.h"

#include "../paymentmethod/HoldMethod.h"

ChangeHoldMethodTransaction::ChangeHoldMethodTransaction(int empid)
    : ChangeMethodTransaction(empid)
{
}

PaymentMethod* ChangeHoldMethodTransaction::GetMethod() const
{
    return new HoldMethod();
}
