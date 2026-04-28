#include "BitcoinExchange.hpp"


void parse_file(std::list<int> &t_array, double &value, std::stringstream &ss, char separator)
{
    std::string buff_str;
    std::list<int>::const_iterator it = t_array.begin();

    for (unsigned int i = 0; i < 3; i++, it++)//set the date with wrapper of stol
    {
        std::getline(ss, buff_str, (i < 2 ? '-': separator));
        t_array.push_back(wrapper_strtol(buff_str));
    }
    if (!is_valid_date(t_array))//check if the date is valid
    {
        std::stringstream ss_error;
        it = t_array.begin();
        ss_error << "bad input => " << *it++ << "-" << std::setfill('0') << std::setw(2) << *it++ << "-" << std::setfill('0') << std::setw(2) << *it++; 
        throw std::invalid_argument(ss_error.str());
    }
    std::getline(ss, buff_str);
    value = wrapper_strtod(buff_str);//buff_str
}

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

bool is_valid_date(std::list<int> t_array)
{
    static int month[] =  MONTH;
    std::list<int>::const_iterator it_3 = t_array.begin();
    std::list<int>::const_iterator it_1 = it_3++;
    std::list<int>::const_iterator it_2 = it_3++;
    if (*it_1 > 0)
    {
        if (*it_2 > 0 && *it_2 <= 12)
        {
            if (*it_2 == 2 && bixetile(*it_1) >= *it_3 && *it_3 > 0)
                return true;
            else if (month[*it_2 - 1] >= *it_3 && *it_3 > 0)
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
        std::list<int> t_array;
        std::stringstream ss(str);
        double value;

        parse_file(t_array, value, ss, SEPARATOR_DATA_FILE);
        if (value < 0)
            throw std::invalid_argument("negatif number");
        this->_data.insert(std::pair<std::list<int>, double> (t_array, value));
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
    std::map<std::list<int>, double>::const_iterator it_begin = this->_data.begin();
    std::map<std::list<int>, double>::const_iterator it_end = this->_data.end();
    std::list<int>::const_iterator it_list;
    for (;it_begin != it_end; it_begin++)
    {
        it_list = it_begin->first.begin();
        std::cout <<  *it_list << " change for : " << it_begin->second <<  std::endl;
    }
}

const std::map<std::list<int>, double>&     BitcoinExchange::get_map()const
{
    return (this->_data);
}
