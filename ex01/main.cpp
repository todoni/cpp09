#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN [expression]" << std::endl;
        return (1);
    }

    std::string expression = std::string(argv[1]);
    RPN rpn;

    try
    {
        std::cout << rpn.calculate(expression) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return (0);
}