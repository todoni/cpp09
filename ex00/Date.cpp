#include "Date.hpp"

Date::Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}

Date::Date(const Date& other) : _year(other._year), _month(other._month), _day(other._day) {}

Date::~Date() {}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValidDate() const
{
    if (_month < 1 || _month > 12)
    {
        return false;
    }
    if (_day < 1)
    {
        return false;
    }
    if (_month == 2)
    {
        if (isLeapYear(_year))
        {
            return _day <= 29;
        }
        else
        {
            return _day <= 28;
        }
    }
    else if (_month == 4 || _month == 6 || _month == 9 || _month == 11)
    {
        return _day <= 30;
    }
    else
    {
        return _day <= 31;
    }
}

Date& Date::operator=(const Date& other)
{
    if (this != &other)
    {
        _year = other._year;
        _month = other._month;
        _day = other._day;
    }
    return (*this);
}

bool Date::operator<(const Date &other) const
{
    if (_year != other._year)
    {
        return _year < other._year;
    }
    else if (_month != other._month)
    {
        return _month < other._month;
    }
    else
    {
        return _day < other._day;
    }
}

bool Date::operator==(const Date &other) const
{
    return (_year == other._year && _month == other._month && _day == other._day);
}

bool Date::operator!=(const Date &other) const
{
    return !(*this == other);
}

int Date::year() const { return _year; }
int Date::month() const { return _month; }
int Date::day() const { return _day; }

std::ostream &operator<<(std::ostream &out, const Date &date)
{
    int year = date.year();
    int month = date.month();
    int day = date.day();

    out << year << "-";
    if (month < 10)
    {
        out << "0" << month;
    }
    else
    {
        out << month;
    }
    out << "-";
    if (day < 10)
    {
        out << "0" << day;
    }
    else
    {
        out << day;
    }
    return out;
}