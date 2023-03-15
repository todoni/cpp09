#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <list>
# include <string>
# include <ostream>
# include <istream>
# include <fstream>

typedef std::map<std::string, float> data;
typedef std::list<std::pair<std::string, float> > input;

class   BitcoinExchange {

private:
    BitcoinExchange(const BitcoinExchange &ref);
    BitcoinExchange &operator=(const BitcoinExchange &ref);

public:
    data database;
    input input_list;
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(std::ifstream& rawDatabase , std::ifstream& rawInput);
    std::list<float> calculate() const;
    
};

std::ostream &operator<<(std::ostream &out, const BitcoinExchange& btc);

#endif