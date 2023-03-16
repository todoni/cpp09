#ifndef DATE_HPP
# define DATE_HPP

# include <ostream>

class Date
{
public:
    Date(int year, int month, int day);
    Date(const Date& other);
    ~Date() {}

    bool operator<(const Date &other) const;
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;

    int year() const { return _year; }
    int month() const { return _month; }
    int day() const { return _day; }

private:
    int _year;
    int _month;
    int _day;

    Date();
    Date& operator=(const Date& ohter);
};

std::ostream& operator<<(std::ostream& out, const Date& date);

#endif