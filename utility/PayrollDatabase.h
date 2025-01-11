#pragma once

#include <list>
#include <map>
#include "Employee.h"

class PayrollDatabase
{
public:
    PayrollDatabase() = default;
    virtual ~PayrollDatabase() = default;

    Employee* GetEmployee(int empId);
    void GetAllEmployeeIds(std::list<int>& empIdList);
    void AddEmployee(int empId, Employee*);
    void DeleteEmployee(int empId);
    void clear() { itsEmployees.clear(); }

    void AddUnionMember(int unionId, Employee* e);
    void RemoveUnionMember(int memberId);

    Employee* GetUnionMember(int memberId);

private:
    std::map<int, Employee*> itsEmployees;
    std::map<int, Employee*> itsUnions;
};