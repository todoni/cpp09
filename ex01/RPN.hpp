#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{

private:
    std::stack<long> calculateStack;

    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    bool isOperator(const std::string& token) const;
    bool isValidNumber(const std::string& token, long number) const;

public:
    RPN();
    ~RPN();
    long calculate(const std::string& expression);

};

#endif