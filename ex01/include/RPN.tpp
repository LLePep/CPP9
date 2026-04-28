template <typename T>
void RPN<T>::calcul(std::stack<double>& d_stack, char my_operator)const
{
    if (d_stack.size() < 2)
        throw std::logic_error("Not enought figure");
    double result = d_stack.top();
    d_stack.pop();
    if (my_operator == '+')
        d_stack.top() = d_stack.top() + result;
    else if (my_operator == '-')
        d_stack.top() = d_stack.top() - result;
    else if (my_operator == '*')
        d_stack.top() = d_stack.top() * result;
    else// '/'
    {
        if (result == 0)//not possible division
            throw std::logic_error("Division by '0' be carefull");
        d_stack.top() = d_stack.top() / result;
    }
};

template <typename T>
double RPN<T>::calculate()const
{
    std::stack<double> d_stack;

    return (calculate(d_stack, this->c.begin()));
};

template <typename T>
double RPN<T>::calculate(std::stack<double>& d_stack, typename std::stack<T>::container_type::const_iterator it)const
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

template <typename T>
void RPN<T>::fill(std::string& str)
{
    for (std::string::iterator it = str.begin(); it != str.end(); it++)
    {
        if (isdigit(*it) || IS_OPERATOR(*it))
        {
            this->push(*it++);
            if (!(*it))
                break;
            else if (!isspace(*it))
                throw std::invalid_argument("Invalid argument");
        }
        else if (!isspace(*it))
            throw std::invalid_argument("Invalid element");
    }
};
