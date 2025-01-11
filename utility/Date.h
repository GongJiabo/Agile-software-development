#pragma once

class Date
{
public:
    enum DAY_NAME
    {
        monday = 0,
        tuesday,
        wednesday,
        thursday,
        friday,
        staturday,
        sunday
    };

    Date(int month, int day, int year);
    explicit Date(int timeNumberStr);
    Date(const Date& date);
    virtual ~Date() = default;

    int GetDay() const { return itsDay; }
    int GetMonth() const { return itsMonth; }
    int GetYear() const { return itsYear; }

    Date::DAY_NAME GetDayOfWeek() const;

    Date& operator=(const Date& d);
    bool operator==(const Date& otherDate) const;
    bool operator!=(const Date& otherDate) const;
    bool operator>(const Date& otherDate) const;
    bool operator<(const Date& otherDate) const;
    bool operator<=(const Date& otherDate) const;
    bool operator>=(const Date& otherDate) const;
    Date& operator+=(int days);
    Date& operator-=(int days);
    Date operator+(int days) const;
    Date operator-(int days) const;
    Date operator++(int); // back a++
    Date& operator++();   // front ++a
    Date operator--(int); // back a--
    Date& operator--();   // front --a
    int operator-(const Date& otherDate) const;

    static bool IsLastDayOfMonth(const Date& date);

private:
    int IsLeapYear() const;
    int GetDayByYearAndMonth() const;

private:
    int itsMonth;
    int itsDay;
    int itsYear;
    DAY_NAME itsDayName;
};
