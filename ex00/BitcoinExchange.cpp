#include "BitcoinExchange.hpp"
#include <vector>
#include <sstream>
#include <iostream>

std::vector<std::string> split(std::string str, char sep)
{
    std::istringstream iss(str);
    std::string buffer;

    std::vector<std::string> result;

    while (std::getline(iss, buffer, sep))
        result.push_back(buffer);
    return (result);
}

bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool is_valid_date(int year, int month, int day)
{
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1)
    {
        return false;
    }
    if (month == 2)
    {
        if (is_leap_year(year))
        {
            return day <= 29;
        }
        else
        {
            return day <= 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return day <= 30;
    }
    else
    {
        return day <= 31;
    }
}

BitcoinExchange::BitcoinExchange(std::ifstream& rawDatabase)
{
    while (!rawDatabase.eof())
    {
        std::string date;
        std::string price;
        getline(rawDatabase, date, ',');
        getline(rawDatabase, price, '\n');
        
        std::vector<std::string> yearMonthDay = split(date, '-');
        if (yearMonthDay.size() == 3)
        {
            database[Date(std::atoi(yearMonthDay[0].c_str()), std::atoi(yearMonthDay[1].c_str()), std::atoi(yearMonthDay[2].c_str()))] = static_cast<float>(std::atof(price.c_str()));
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

void    BitcoinExchange::doExchange(std::string rawInput)
{
    if (rawInput.empty())
    {
        return ;
    }
    std::vector<std::string> dateValue = split(rawInput, '|');
    if (dateValue.size() != 2)
    {
        std::cout << "Error: " << rawInput << " : Bad Input" << std::endl;
        return ;
    }
    std::vector<std::string> date = split(dateValue[0], '-');
    int year = -1;
    int month = -1;
    int day = -1;
    float quantity = -1;
    if (date.size() == 3)
    {
        year = std::atoi(date[0].c_str());
        month = std::atoi(date[1].c_str());
        day = std::atoi(date[2].c_str());
        quantity = static_cast<float>(std::atof(dateValue[1].c_str()));
    }
    if (year == -1 && month == -1 && day == -1 && quantity == -1)
    {
        return ;
    }
    Date targetDate(year, month, day);
    if (!is_valid_date(year, month, day))
    {
        std::cout << "Error: " << targetDate << ": Invalid Date" << std::endl;
    }
    else if (quantity < 0)
    {
        std::cout << "Error:" << quantity << ": Number must be positive" << std::endl;
    }
    else if (quantity > 1000)
    {
        std::cout << "Error:" << quantity << ": Number too big" << std::endl;
    }
    else
    {
        std::map<Date, float>::const_iterator price = database.upper_bound(targetDate);
        if (price != database.begin())
            --price;
        std::cout << "Date: " << targetDate << "\nPrice: " << price->second << " Quantity: " << quantity << " => " << price->second * quantity << std::endl;
    }
}