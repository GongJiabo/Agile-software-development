#pragma once

class Transaction
{
public:
    virtual ~Transaction();
    virtual void Execute() = 0;
};
