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

    void calcul(std::stack<double>& d_stack, char my_operator)const;

    double calculate()const;

    double calculate(std::stack<double>& d_stack, typename std::stack<T>::container_type::const_iterator it)const;

    void fill(std::string& str);
};

#include "RPN.tpp"

#endif