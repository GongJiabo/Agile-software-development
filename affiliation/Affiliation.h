#pragma once

#include "../utility/PayCheck.h"

class Affiliation
{
public:
    Affiliation() = default;
    virtual ~Affiliation() = default;

    virtual double CalculateDeductions(const PayCheck& payCheck) = 0;
};
