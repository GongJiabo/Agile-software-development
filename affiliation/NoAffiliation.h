#pragma once

#include "Affiliation.h"

class NoAffiliation : public Affiliation
{
public:
    NoAffiliation() = default;
    virtual ~NoAffiliation() = default;

    double CalculateDeductions(const PayCheck& payCheck) override;
};