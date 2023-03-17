#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2 || !argv[1])
        return (1);

    std::ifstream rawInput;
    std::ifstream rawDatabase;

    rawInput.open(argv[1]);
    if (rawInput.fail())
    {
        std::cout << "input error" << std::endl;
        return (1);
    }
    rawDatabase.open("data.csv");
    if (rawDatabase.fail())
    {   
        std::cout << "db error" << std::endl;
        return (1);
    }

    
    BitcoinExchange btc(rawDatabase);
    
        while (!rawInput.eof())
    {
        std::string dateValue;
        getline(rawInput, dateValue, '\n');
        btc.doExchange(dateValue);
    }
    
}
