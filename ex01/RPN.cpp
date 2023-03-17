#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

bool RPN::isOperator(const char& token) const
{
    return (token == '+' || token == '-' || token == '/' || token == '*');
}

long RPN::calculate(std::string expression)
{
    for (std::string::iterator token = expression.begin(); token != expression.end(); ++token)
    {
        if (std::isdigit(*token))
        {
            int operand = *token - '0';
            calculateStack.push(operand);
        }
        else if (isOperator(*token)) 
        {
            if (calculateStack.size() < 2)
                throw std::runtime_error("Error");
            
            long a = calculateStack.top();
            calculateStack.pop();
            long b = calculateStack.top();
            calculateStack.pop();

            if (*token == '+')
                calculateStack.push(b + a);
            else if (*token == '-')
                calculateStack.push(b - a);
            else if (*token == '/')
            {
                if (a == 0)
                {
                    throw std::runtime_error("Error");
                }
                calculateStack.push(b / a);
            }
            else if (*token == '*')
                calculateStack.push(b * a);
        }
        else if (*token == ' ')
        {

        }
        else
        {
            throw std::invalid_argument("Error");
        }
    }
    if (calculateStack.size() != 1)
        throw std::runtime_error("Error");
    return calculateStack.top();
}