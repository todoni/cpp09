#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <fstream>

# include "Date.hpp"

typedef std::map<Date, float> data;

class   BitcoinExchange
{
private:
    data database;
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &ref);
    BitcoinExchange& operator=(const BitcoinExchange &ref);

public:
    ~BitcoinExchange();
    BitcoinExchange(std::ifstream& rawDatabase);
    float getExchangeRateOftheday(Date date);
    void doExchange(std::string rawInput);

};

#endif