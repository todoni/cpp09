#include "BitcoinExchange.hpp"
#include "color.hpp"
#include <queue>
#include <iostream>

std::string& ltrim(std::string &s, const std::string& t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

std::string& rtrim(std::string &s, const std::string& t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

std::string& trim(std::string &s, const std::string& t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

std::queue<std::string> split(std::string str, std::string delimiter)
{
    std::queue<std::string> result;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push(token);
        str.erase(0, pos + delimiter.length());
    }
    if (str != "")
        result.push(trim(str));
    return (result);
}

BitcoinExchange::BitcoinExchange(std::ifstream& rawDatabase)
{
    std::string date;
    std::string price;
    while (std::getline(rawDatabase, date, ',') && std::getline(rawDatabase, price, '\n'))
    {
        if (rawDatabase.fail())
        {
            std::cout << "Error while read DB file" << std::endl;
            break;
        }
        std::queue<std::string> yearMonthDay = split(date, "-");
        if (yearMonthDay.size() == 3)
        {
            int year = std::atoi(yearMonthDay.front().c_str());
            yearMonthDay.pop();
            int month = std::atoi(yearMonthDay.front().c_str());
            yearMonthDay.pop();
            int day = std::atoi(yearMonthDay.front().c_str());
            yearMonthDay.pop();
            
            database[Date(year, month, day)] = static_cast<float>(std::atof(price.c_str()));
        }
    }
}

BitcoinExchange::~BitcoinExchange() {}

void    BitcoinExchange::doExchange(std::string rawInput)
{
    if (rawInput.empty() || rawInput == "date | value")
    {
        return ;
    }

    std::queue<std::string> dateValue = split(rawInput, " | ");
    if (dateValue.size() != 2)
    {
        std::cout << "Error: " << rawInput << " : Bad Input" << std::endl;
        return ;
    }

    std::queue<std::string> yearMonthDay = split(dateValue.front(), "-");
    if (yearMonthDay.size() != 3)
    {
        std::cout << "Error: " << dateValue.front() << " : Bad Input" << std::endl;
        return ;
    }
    
    float quantity = static_cast<float>(std::atof(dateValue.back().c_str()));

    int year = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();
    int month = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();
    int day = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();

    Date targetDate(year, month, day);
    
    if (!targetDate.isValidDate())
    {
        std::cout << "Error: " << dateValue.front() << " : Invalid Date" << std::endl;
    }
    else if (quantity == 0)
    {
        std::cout << "Error: " << dateValue.back() << " : Invalid value" << std::endl;
    }
    else if (quantity < 0)
    {
        std::cout << "Error: " << quantity << " : Number must be positive" << std::endl;
    }
    else if (quantity >= 1000)
    {
        std::cout << "Error: " << quantity << " : Number too big" << std::endl;
    }
    else
    {
        std::map<Date, float>::const_iterator price = database.upper_bound(targetDate);
        if (price != database.begin())
            --price;
        std::cout << targetDate << " => " << YELLOW << price->second << END << " * " << YELLOW << quantity << END << " = " << price->second * quantity << "💰" << END << std::endl;
    }
}