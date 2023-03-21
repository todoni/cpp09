#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./btc [file name]" << std::endl;
        return (1);
    }
    std::ifstream rawInput;
    std::ifstream rawDatabase;

    rawInput.open(argv[1]);
    if (!rawInput.is_open())
    {
        std::cout << "Input File Open Error" << std::endl;
        return (1);
    }
    rawDatabase.open("data.csv");
    if (!rawDatabase.is_open())
    {   
        std::cout << "DB File Open error" << std::endl;
        return (1);
    }
    
    BitcoinExchange btc(rawDatabase);
    
    std::string dateValue;
    while (std::getline(rawInput, dateValue, '\n'))
    {
        if (rawInput.fail())
        {
            std::cout << "Error while reading file" << std::endl;
            return (1);
        }
        btc.doExchange(dateValue);
    }

   return (0); 
}
