#ifndef DATE_HPP
# define DATE_HPP

# include <ostream>

class Date
{
public:
    Date(int year, int month, int day);
    Date(const Date& other);
    ~Date();
    Date& operator=(const Date& ohter);

    bool operator<(const Date &other) const;
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;

    int year() const;
    int month() const;
    int day() const;

    bool isValidDate() const;

private:
    int _year;
    int _month;
    int _day;
    
    Date();

};

std::ostream& operator<<(std::ostream& out, const Date& date);

#endif