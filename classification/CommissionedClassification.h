#pragma once

#include <vector>
#include "../utility/SalesReceipt.h"
#include "../classification/PaymentClassification.h"

class CommissionedClassification : public PaymentClassification
{
public:
    explicit CommissionedClassification(double salary, double commissionRate);
    virtual ~CommissionedClassification() = default;

    double CalculatePay(const PayCheck& pc) override;

    void AddSalesReceipt(SalesReceipt* salesReceipt);
    SalesReceipt* GetSalesReceipt(const Date& date) const;
    double GetCommissionRate() const;
    double GetSalary() const;

private:
    std::vector<SalesReceipt*> itsSalesReceipt;
    double itsSalary;
    double itsCommissionRate;
};