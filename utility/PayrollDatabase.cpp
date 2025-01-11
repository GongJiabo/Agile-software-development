#include "PayrollDatabase.h"
#include "Employee.h"

PayrollDatabase GpayrollDatabase;

Employee* PayrollDatabase::GetEmployee(int empId)
{
    return itsEmployees[empId];
}

void PayrollDatabase::GetAllEmployeeIds(std::list<int>& empIdList)
{
    empIdList.clear();
    for (const auto& pair : itsEmployees)
    {
        empIdList.push_back(pair.first);
    }
}

void PayrollDatabase::AddEmployee(int empId, Employee* e)
{
    if (itsEmployees.find(empId) != itsEmployees.end()){
        delete itsEmployees[empId];
    }
    itsEmployees[empId] = e;
}

void PayrollDatabase::DeleteEmployee(int empId) { itsEmployees.erase(empId); }

void PayrollDatabase::AddUnionMember(int unionId, Employee* e)
{
    itsUnions[unionId] = e;
}

void PayrollDatabase::RemoveUnionMember(int memberId)
{
    itsUnions.erase(memberId);
}

Employee* PayrollDatabase::GetUnionMember(int memberId)
{
    return itsUnions[memberId];
}
