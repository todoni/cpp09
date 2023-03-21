#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <fstream>

# include "Date.hpp"


class   BitcoinExchange
{
typedef std::map<Date, float> data;

private:
    data database;
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &ref);
    BitcoinExchange& operator=(const BitcoinExchange &ref);

public:
    ~BitcoinExchange();
    BitcoinExchange(std::ifstream& rawDatabase);
    void doExchange(std::string rawInput);

};

#endif