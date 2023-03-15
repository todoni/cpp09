#include "BitcoinExchange.hpp"
#include <iostream>



int main(int argc, char** argv)
{
    if (argc != 2)
        return (1);

    std::ifstream rawInput;
    std::ifstream rawDatabase;

    rawInput.clear();
    rawDatabase.clear();

    rawInput.open(argv[1]);
    if (rawInput.fail())
        std::cerr << "input error" << std::endl;
        rawInput.close();
    return (1);

    rawDatabase.open("data.csv");
    if (rawDatabase.fail())
    {   
        std::cerr << "db error" << std::endl;
        rawDatabase.close();
        return (1);
    }

    
    BitcoinExchange btc(rawDatabase, rawInput);
    
    /*while (!rawDatabase.eof())
    {
        std::string date;
        std::string value;
        getline(rawDatabase, date, ',');
        getline(rawDatabase, value, '\n');
        btc.database[date] = std::stof(value);
    }

    while (!rawInput.eof())
    {
        std::string date;
        std::string value;
        getline(rawInput, date, '|');
        getline(rawInput, value, '\n');
        btc.input_list.push_back(std::make_pair(trim(date), std::stof(trim(value))));
    }*/

        std::cout << btc << std::endl;
    }