#pragma once

#include "ChangeAffiliationTransaction.h"

class ChangeUnaffiliatedTransaction : public ChangeAffiliationTransaction
{
public:
    explicit ChangeUnaffiliatedTransaction(int empId);
    virtual ~ChangeUnaffiliatedTransaction() = default;

    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;
};