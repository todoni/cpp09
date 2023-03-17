#include "Date.hpp"

Date::Date() : _year(0), _month(0), _day(0) {}

Date::Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}

Date::Date(const Date& other) : _year(other._year), _month(other._month), _day(other._day) {}

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