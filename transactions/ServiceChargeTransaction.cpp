#include "ServiceChargeTransaction.h"

#include "../affiliation/UnionAffiliation.h"
#include "../utility/Employee.h"
#include "../utility/PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

ServiceChargeTransaction::ServiceChargeTransaction(int memberId,
                                                   const Date& date,
                                                   double charge)
    : itsMemberId(memberId), itsDate(date), itsCharge(charge)
{
}

void ServiceChargeTransaction::Execute()
{
    Employee* e = GpayrollDatabase.GetUnionMember(itsMemberId);
    Affiliation* af = e->GetAffiliation();
    if (UnionAffiliation* uaf = dynamic_cast<UnionAffiliation*>(af))
    {
        uaf->AddServiceCharge(itsDate, itsCharge);
    }
}
