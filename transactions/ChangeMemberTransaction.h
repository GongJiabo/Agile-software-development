#pragma once

#include "ChangeAffiliationTransaction.h"

class ChangeMemberTransaction : public ChangeAffiliationTransaction
{
public:
    ChangeMemberTransaction(int empid, int memberid, double dues);
    virtual ~ChangeMemberTransaction() = default;

    Affiliation* GetAffiliation() const override;
    void RecordMembership(Employee*) override;

private:
    int itsMemberId;
    double itsDues;
};
