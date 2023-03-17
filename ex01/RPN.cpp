#include "RPN.hpp"
#include <sstream>
#include <iostream>

RPN::RPN() {}

RPN::~RPN() {}

std::string numToString(long num)
{
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

bool RPN::isOperator(const std::string &token) const
{
    if (token != "*" && token != "/" && token != "-" && token != "+")
        return false;
    return true;
}

bool RPN::isValidNumber(const std::string& token, long number) const
{
    return (numToString(number) == token);
}

long RPN::calculate(const std::string& expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (std::getline(iss, token, ' '))
    {
        long number = std::atoi(token.c_str());

        if (!isValidNumber(token, number) && !isOperator(token))
            throw std::invalid_argument("Error");
        
        if (isOperator(token))
        {
            if (calculateStack.size() < 2)
                throw std::invalid_argument("Error");
            
            long a = calculateStack.top();
            calculateStack.pop();
            long b = calculateStack.top();
            calculateStack.pop();

            if (token == "+")
                calculateStack.push(b + a);
            else if (token == "-")
                calculateStack.push(b - a);
            else if (token == "/")
                calculateStack.push(b / a);
            else if (token == "*")
                calculateStack.push(b * a);
        }
        else
        {
            calculateStack.push(number);
        }    
    }
    if (calculateStack.size() != 1)
        throw std::runtime_error("Error");
    return calculateStack.top();
}