#include "BitcoinExchange.hpp"

static int bixetile(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 && !(year % 400))
            return 28;
        return 29;
    }
    else
        return 28;
}

bool is_valid_date(std::vector<int> t_array)
{
    static int month[] =  MONTH;
    if (t_array[0] > 0)
    {
        if (t_array[1] > 0 && t_array[1] <= 12)
        {
            if (t_array[1] == 2 && bixetile(t_array[0]) >= t_array[2] && t_array[2] > 0)
                return true;
            else if (month[t_array[1] - 1] >= t_array[2] && t_array[2] > 0)
                return true;
            else
                return false;
        }
        else//Error of Month
        {
            return (false);}
    }
    else//Error of Year
    {
        return (false);}
}

double wrapper_strtod(const std::string& str)
{
    double value;
    char* endptr;
    errno = 0;

    value = strtod(str.c_str(), &endptr);
    while (*endptr != '\0')
    {
        if (!isdigit(*endptr) && !isspace(*endptr))
            throw std::invalid_argument("Not recognize a valid number");
        endptr++;
    }
    if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
        throw std::invalid_argument("too large a number");
    if (errno == ERANGE)
        throw std::invalid_argument("number out of range");
    return (value);
}

int wrapper_strtol(const std::string& str)
{
    char* endptr;
    long int to_return;
    errno = 0;

    to_return = std::strtol(str.c_str(), &endptr, 10);
    while (*endptr != '\0')
    {
        if (!isdigit(*endptr) && !isspace(*endptr))
            throw std::invalid_argument("Not recognize a valid number");
        endptr++;
    }
    if (errno == ERANGE)
        throw std::invalid_argument("number out of range");
    return (static_cast<int> (to_return));
}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange()
{
    std::ifstream ifs;
    ifs.open(DATA_BASE, std::ifstream::in);
    if (!ifs.is_open())//Open fail or Not 
        throw std::runtime_error("Open fail");
    std::string str;
    std::getline(ifs, str);
    if (str != "date,exchange_rate")//check the first line
        throw std::invalid_argument("Invalid base");
    while (std::getline(ifs, str))//fill my object with my file
    {
        std::vector<int> t_array(3);
        std::stringstream ss(str);
        std::string buff_str;
        double value;

        for (unsigned int i = 0; i < 3; i++)//set the date with wrapper of stol
        {
            std::getline(ss, buff_str, (i < 2 ? '-': ','));
            t_array[i] = wrapper_strtol(buff_str);
        }
        if (!is_valid_date(t_array))//check if the date is valid
        {
            std::stringstream ss_error;
            ss_error << "bad input => " << t_array[0] << "-" << std::setfill('0') << std::setw(2) << t_array[1] << "-" << std::setfill('0') << std::setw(2) << t_array[2]; 
            throw std::invalid_argument(ss_error.str());
        }
        std::getline(ss, buff_str);
        value = wrapper_strtod(buff_str);
        if (value < 0)
            throw std::invalid_argument("negatif number");
        this->_data.insert(std::pair<std::vector<int>, double> (t_array, value));
    }
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& toCopy)
{
    if (this == &toCopy)
        return (*this);
    this->_data = toCopy._data;
    return (*this);
}

void BitcoinExchange::print()const
{
    std::map<std::vector<int>, double>::const_iterator it_begin = this->_data.begin();
    std::map<std::vector<int>, double>::const_iterator it_end = this->_data.end();
    for (;it_begin != it_end; it_begin++)
    {
        std::cout << it_begin->first[0] << " change for : " << it_begin->second <<  std::endl;
    }
}

const std::map<std::vector<int>, double>&     BitcoinExchange::get_map()const
{
    return (this->_data);
}
