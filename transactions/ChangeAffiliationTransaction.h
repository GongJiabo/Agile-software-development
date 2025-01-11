#pragma once

#include "ChangeEmployeeTransaction.h"

class ChangeAffiliationTransaction : public ChangeEmployeeTransaction
{
public:
    explicit ChangeAffiliationTransaction(int empid);
    virtual ~ChangeAffiliationTransaction() = default;

    virtual Affiliation* GetAffiliation() const = 0;
    virtual void RecordMembership(Employee*) = 0;
    virtual void Change(Employee&);
};
