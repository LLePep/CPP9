#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <iostream>

#define IS_OPERATOR(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/')

template <typename T>
class RPN : public std::stack<T>{

private:
    RPN &operator=(const RPN &toCopy)
    {
        if (this == &toCopy)
        {return (this);}
        this->c = toCopy.c;
        return (this);
    };

public:
    ~RPN() {};
    RPN(): std::stack<T>() {};
    RPN(const RPN &toCopy): std::stack<T>(toCopy) {};

    void calcul(std::stack<double>& d_stack, char my_operator)const
    {
        if (d_stack.size() < 2)
            throw std::logic_error("Not enought figure");
        
        double result = d_stack.top();
        d_stack.pop();
        if (my_operator == '+')
            result = d_stack.top() + result;
        else if (my_operator == '-')
            result = d_stack.top() - result;
        else if (my_operator == '*')
            result = d_stack.top() * result;
        else// '/' faire la division par zero
        {
            if (result == 0)
                throw std::;//not possible division
            result = d_stack.top() / result;
        }
        d_stack.pop();
        d_stack.push(result);
    };

    double calculate()const
    {
        std::stack<double> d_stack;

        return (calculate(d_stack, this->c.begin()));
    };

    double calculate(std::stack<double>& d_stack, typename std::stack<T>::container_type::const_iterator it)const
    {
        if (isdigit(*it))
        {
            d_stack.push(*it - '0');
            return (calculate (d_stack, ++it));
        }
        else if (IS_OPERATOR(*it))
        {
            calcul(d_stack, *it);
            return (calculate(d_stack, ++it));
        }
        else
        {
            if (d_stack.size() != 1)
                throw std::logic_error("Not the end of operation");
            return (d_stack.top());
        }
    };

    void fill(std::string& str)
    {
        for (std::string::iterator it = str.begin(); it != str.end(); it++)
        {
            if (isdigit(*it) || IS_OPERATOR(*it))
                this->push(*it);
            else if (!isspace(*it))
                throw std::invalid_argument("Invalid element");
        }
    };
};


#endif