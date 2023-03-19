#include "BitcoinExchange.hpp"
#include <queue>
#include <iostream>

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
        result.push(str);
    return (result);
}

BitcoinExchange::BitcoinExchange(std::ifstream& rawDatabase)
{
    while (!rawDatabase.eof())
    {
        std::string date;
        std::string price;
        getline(rawDatabase, date, ',');
        getline(rawDatabase, price, '\n');
        
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

bool    isValidDateFormat(std::string date)
{
    for (std::string::iterator it = date.begin(); it != date.end(); ++it)
    {
        if (!std::isdigit(*it) && *it != '-')
            return false;
    }
    return true;
}

bool    isValidValueFormat(std::string valueString, float value)
{
    if (value == 0 && valueString != "0")
        return false;
    return true;
}

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
    if (!isValidDateFormat(dateValue.front()))
    {
        std::cout << "Error: " << dateValue.front() << " : Invalid Date Format" << std::endl;
        return ;
    }

    float quantity = static_cast<float>(std::atof(dateValue.back().c_str()));
    if (!isValidValueFormat(dateValue.back(), quantity))
    {
        std::cout << "Error: " << dateValue.back() << " : Invalid Value" << std::endl;
        return;
    }

    std::queue<std::string> yearMonthDay = split(dateValue.front(), "-");
    if (yearMonthDay.size() != 3)
    {
        std::cout << "Error: " << dateValue.front() << " : Bad Input" << std::endl;
        return ;
    }

    int year = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();
    int month = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();
    int day = std::atoi(yearMonthDay.front().c_str());
    yearMonthDay.pop();

    Date targetDate(year, month, day);
    
    if (!targetDate.isValidDate())
    {
        std::cout << "Error: " << targetDate << " : Invalid Date" << std::endl;
    }
    else if (quantity <= 0)
    {
        std::cout << "Error: " << quantity << " : Number must be positive" << std::endl;
    }
    else if (quantity > 1000)
    {
        std::cout << "Error: " << quantity << " : Number too big" << std::endl;
    }
    else
    {
        std::map<Date, float>::const_iterator price = database.upper_bound(targetDate);
        if (price != database.begin())
            --price;
        std::cout << targetDate << " => " << price->second << " * " << quantity << " = " << price->second * quantity << std::endl;
    }
}