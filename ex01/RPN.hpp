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
    bool isOperator(const char& token) const;

public:
    RPN();
    ~RPN();
    long calculate(std::string expression);
};

#endif