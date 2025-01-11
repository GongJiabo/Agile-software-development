#pragma once

#include <map>
#include "../affiliation/Affiliation.h"
#include "../utility/Date.h"
#include "../utility/PayCheck.h"
#include "../utility/ServiceCharge.h"

class UnionAffiliation : public Affiliation
{
public:
    UnionAffiliation() = default;
    explicit UnionAffiliation(int id);
    UnionAffiliation(int id, double dues);
    virtual ~UnionAffiliation() = default;

    double CalculateDeductions(const PayCheck& payCheck) override;

    ServiceCharge* GetServiceCharge(const Date& date) const;
    void AddServiceCharge(const Date& date, double charge);
    int GetMemberId() const { return itsUnionId; }
    double GetDues() const { return itsDues; }

private:
    int NumberOfFridaysInpayPeriod(const Date& payPeriodStart,
                                   const Date& payPeriodEnd);

private:
    int itsUnionId;
    double itsDues;
    std::map<Date, ServiceCharge*> itsServiceCharges;
};
