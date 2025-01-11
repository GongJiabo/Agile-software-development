#include "Date.h"

#include <string>

Date::Date(int month, int day, int year)
    : itsMonth(month), itsDay(day), itsYear(year)
{
    // 使用基姆拉尔森计算公式
    if (month == 1 || month == 2)
    {
        month += 12;
        year--;
    }
    itsDayName = DAY_NAME((day + 2 * month + 3 * (month + 1) / 5 + year +
                           year / 4 - year / 100 + year / 400) %
                          7);
}

Date::Date(int timeNumberStr)
{
    std::string timeStr = std::to_string(timeNumberStr);
    if (timeStr.size() != 8)
    {
        return;
    }
    itsYear = std::stoi(timeStr.substr(0, 4));
    itsMonth = std::stoi(timeStr.substr(4, 2));
    itsDay = std::stoi(timeStr.substr(6, 2));
}

Date::Date(const Date& date)
{
    itsYear = date.itsYear;
    itsMonth = date.itsMonth;
    itsDay = date.itsDay;
    itsDayName = date.itsDayName;
}

Date::DAY_NAME Date::GetDayOfWeek() const { return itsDayName; }

Date& Date::operator=(const Date& d)
{
    if (this != &d)
    {
        this->itsYear = d.itsYear;
        this->itsMonth = d.itsMonth;
        this->itsDay = d.itsDay;
        this->itsDayName = d.itsDayName;
    }
    return *this;
}

bool Date::operator==(const Date& otherDate) const
{
    if (itsDay == otherDate.itsDay && itsMonth == otherDate.itsMonth &&
        itsYear == otherDate.itsYear)
    {
        return true;
    }
    return false;
}

bool Date::operator!=(const Date& otherDate) const
{
    return !((*this) == otherDate);
}

bool Date::operator>(const Date& otherDate) const
{
    return (
        (itsYear > otherDate.itsYear) ||
        ((itsYear == otherDate.itsYear) && (itsMonth > otherDate.itsMonth)) ||
        ((itsYear == otherDate.itsYear) && (itsMonth == otherDate.itsMonth) &&
         (itsDay > otherDate.itsDay)));
}

bool Date::operator<(const Date& otherDate) const
{
    return (
        (itsYear < otherDate.itsYear) ||
        ((itsYear == otherDate.itsYear) && (itsMonth < otherDate.itsMonth)) ||
        ((itsYear == otherDate.itsYear) && (itsMonth == otherDate.itsMonth) &&
         (itsDay < otherDate.itsDay)));
}

bool Date::operator<=(const Date& otherDate) const
{
    return !((*this) > otherDate);
}

bool Date::operator>=(const Date& otherDate) const
{
    return !((*this) < otherDate);
}

Date& Date::operator+=(int days)
{
    (*this) = (*this) + days;
    return *this;
}

Date& Date::operator-=(int days)
{
    (*this) = (*this) + days;
    return *this;
}

Date Date::operator++(int)
{
    Date tmp(*this);
    *this += 1;
    return tmp;
}

Date& Date::operator++()
{
    *this += 1;
    return *this;
}

Date Date::operator--(int)
{
    *this -= 1;
    return *this;
}

Date& Date::operator--()
{
    *this -= 1;
    return *this;
}

Date Date::operator+(int days) const
{
    Date tmpDate(*this);
    tmpDate.itsDay += days;
    tmpDate.itsDayName = DAY_NAME((tmpDate.itsDayName + days) % 7);
    while (tmpDate.itsDay > GetDayByYearAndMonth())
    {
        tmpDate.itsDay -= GetDayByYearAndMonth();
        tmpDate.itsMonth += 1;
        if (tmpDate.itsMonth > 12)
        {
            tmpDate.itsYear += 1;
            tmpDate.itsMonth = 1;
        }
    }
    return tmpDate;
}

Date Date::operator-(int days) const
{
    Date tmpDate(*this);
    tmpDate.itsDay -= days;
    tmpDate.itsDayName = DAY_NAME((tmpDate.itsDayName - days) % 7);
    while (tmpDate.itsDay <= 0)
    {
        tmpDate.itsMonth -= 1;
        tmpDate.itsDayName = DAY_NAME(tmpDate.itsDayName + 7);
        if (tmpDate.itsMonth <= 0)
        {
            tmpDate.itsYear -= 1;
            tmpDate.itsMonth = 12;
        }
        tmpDate.itsDay = tmpDate.itsDay + GetDayByYearAndMonth();
    }
    return tmpDate;
}

int Date::operator-(const Date& otherDate) const
{
    Date max = (*this);
    Date min = otherDate;
    if (otherDate > *this)
    {
        max = otherDate;
        min = (*this);
    }
    int count = 0;
    while (max != min)
    {
        min++;
        count++;
    }
    return count;
}

bool Date::IsLastDayOfMonth(const Date& date)
{
    int m1 = date.GetMonth();
    int m2 = (date + 1).GetMonth();
    return (m1 != m2);
}

int Date::IsLeapYear() const
{
    if ((itsYear % 4 == 0 && itsYear % 100 != 0) || (itsYear % 400 == 0))
    {
        return 1;
    }
    return 0;
}

int Date::GetDayByYearAndMonth() const
{
    int monthitsDay[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (IsLeapYear() && itsMonth == 2)
    {
        return 29;
    }
    return monthitsDay[itsMonth];
}
