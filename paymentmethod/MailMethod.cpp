#include "MailMethod.h"

#include "../utility/PayCheck.h"

MailMethod::MailMethod(const std::string& address) : itsAddress(address) {}

void MailMethod::Pay(PayCheck& pc) { pc.SetField("Disposition", "Mail"); }

std::string MailMethod::GetAddress() const { return itsAddress; }
