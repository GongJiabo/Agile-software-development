#pragma once

#include <string>

class PaymentSchedule;
class PaymentClassification;
class PaymentMethod;
class Affiliation;
class PayCheck;
class Date;

class Employee
{
public:
    Employee(int empid, std::string name, std::string address);
    virtual ~Employee() = default;

    void SetName(std::string name);
    void SetAddress(std::string address);
    void SetClassification(PaymentClassification*);
    void SetSchedule(PaymentSchedule*);
    void SetMethod(PaymentMethod*);
    void SetAffiliation(Affiliation*);

    int GetEmpid() const { return itsEmpid; }
    std::string GetName() const { return itsName; }
    std::string GetAddress() const { return itsAddress; }
    PaymentMethod* GetMethod() { return itsPaymentMethod; }
    PaymentClassification* GetClassification() { return itsClassification; }
    PaymentSchedule* GetSchedule() { return itsSchedule; }
    Affiliation* GetAffiliation() { return itsAffiliation; }

    void Payday(PayCheck&);
    bool IsPayDate(const Date& payDate) const;
    Date GetPayPeriodStartDate(const Date& payPeriodEndDate) const;

private:
    int itsEmpid;
    std::string itsName;
    std::string itsAddress;
    PaymentClassification* itsClassification;
    PaymentSchedule* itsSchedule;
    PaymentMethod* itsPaymentMethod;
    Affiliation* itsAffiliation;
};