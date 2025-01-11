#pragma once

#include <string>
#include "../paymentmethod/PaymentMethod.h"

class MailMethod : public PaymentMethod
{
public:
    MailMethod() = default;
    explicit MailMethod(const std::string& address);
    virtual ~MailMethod() = default;

    void Pay(PayCheck& payCheck) override;
    std::string GetAddress() const;

private:
    std::string itsAddress;
};