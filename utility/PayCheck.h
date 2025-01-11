#pragma once

#include <map>
#include <string>
#include "Date.h"

class PayCheck
{
public:
    PayCheck(const Date& payPeriodStart, const Date& payPeriodEnd);
    virtual ~PayCheck() = default;

    void SetGrossPay(double grossPay);
    void SetDeductions(double deductions);
    void SetNetPay(double netPay);

    double GetGrossPay() const { return itsGrossPay; }
    double GetDeductions() const { return itsDeductions; }
    double GetNetPay() const { return itsNetPay; }

    Date GetPayPeriodEndDate() const { return itsPayPeriodEndDate; }
    Date GetPayPeriodStartDate() const { return itsPayPeriodStartDate; }
    void SetField(std::string name, std::string value);
    std::string GetField(std::string name);

private:
    Date itsPayPeriodStartDate;
    Date itsPayPeriodEndDate;
    double itsGrossPay;
    double itsNetPay;
    double itsDeductions;
    std::map<std::string, std::string> itsFields;
};