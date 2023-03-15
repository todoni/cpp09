#include "BitcoinExchange.hpp"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

BitcoinExchange::BitcoinExchange(std::ifstream& rawDatabase, std::ifstream& rawInput)
{
    while (!rawDatabase.eof())
    {
        std::string date;
        std::string value;
        getline(rawDatabase, date, ',');
        getline(rawDatabase, value, '\n');
        database[date] = std::stof(value);
    }

    while (!rawInput.eof())
    {
        std::string date;
        std::string value;
        getline(rawInput, date, '|');
        getline(rawInput, value, '\n');
        input_list.push_back(std::make_pair(trim(date), std::stof(trim(value))));
    }
}
BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

std::list<float> BitcoinExchange::calculate() const
{
    std::list<float> result;
    std::list<std::pair<std::string, float> >::const_iterator it = input_list.begin();
    
    for(;it != input_list.end();++it)
        result.push_back(database.find(it->first)->second * it->second);

    return result;
}

std::ostream& operator<<(std::ostream& out, const BitcoinExchange& btc)
{
    std::list<float> result = btc.calculate();
    std::list<float>::iterator it = result.begin();
    
    for (;it != result.end(); ++it)
        out << *it;
    
    return out;
}