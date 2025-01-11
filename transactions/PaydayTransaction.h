#pragma once

#include <map>
#include "Transaction.h"
#include "../utility/Date.h"
#include "../utility/PayCheck.h"

class PaydayTransaction : public Transaction
{
public:
    explicit PaydayTransaction(Date payDate);
    virtual ~PaydayTransaction() = default;
    
    void Execute() override;

    PayCheck* GetPaycheck(int empId);
    int GetPaycheckCount() const;

private:
    Date itsPayDate;
    std::map<int, PayCheck*> itsPaychecks;
};
