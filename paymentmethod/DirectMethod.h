#pragma once

#include "PaymentMethod.h"
#include <string>

class DirectMethod : public PaymentMethod
{
public:
    DirectMethod(const std::string& bankName, const std::string& account);
    virtual ~DirectMethod() = default;

    void Pay(PayCheck& payCheck) override;
    std::string GetBank() const;
    std::string GetAccount() const;

private:
    std::string itsBankName;
    std::string itsAccount;
};