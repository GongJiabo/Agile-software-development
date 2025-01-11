#include "DirectMethod.h"

DirectMethod::DirectMethod(const std::string& bankName,
                           const std::string& account)
    : itsBankName(bankName), itsAccount(account)
{
}

void DirectMethod::Pay(PayCheck& pc) { pc.SetField("Disposition", "Direct"); }

std::string DirectMethod::GetBank() const { return itsBankName; }

std::string DirectMethod::GetAccount() const { return itsAccount; }
