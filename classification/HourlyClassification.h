#pragma once

#include <map>
#include "../utility/Date.h"
#include "../utility/TimeCard.h"
#include "../classification/PaymentClassification.h"

class HourlyClassification : public PaymentClassification
{
public:
    explicit HourlyClassification(double hourlyRate);
    virtual ~HourlyClassification() = default;

    double CalculatePay(const PayCheck& pc) override;

    TimeCard* GetTimeCard(const Date& date);
    void AddTimeCard(const Date& date, TimeCard* timeCard);
    double GetHourlyRate() const;

private:
    double CalculatePayForTimeCard(TimeCard* tc) const;

private:
    std::map<Date, TimeCard*> itsTimeCards;
    double itsHourlyRate;
};