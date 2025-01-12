#include "ChangeMemberTransaction.h"

#include "../affiliation/UnionAffiliation.h"
#include "../utility/PayrollDatabase.h"

extern PayrollDatabase GpayrollDatabase;

ChangeMemberTransaction::ChangeMemberTransaction(int empid, int memberid,
                                                 double dues)
    : ChangeAffiliationTransaction(empid), itsMemberId(memberid), itsDues(dues)
{
}

Affiliation* ChangeMemberTransaction::GetAffiliation() const
{
    return new UnionAffiliation(itsMemberId, itsDues);
}

void ChangeMemberTransaction::RecordMembership(Employee* e)
{
    GpayrollDatabase.AddUnionMember(itsMemberId, e);
}
