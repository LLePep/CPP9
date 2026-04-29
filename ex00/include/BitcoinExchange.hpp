#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <cerrno>

#define MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
#define DATA_BASE "data.csv"

#define SEPARATOR_DATA_FILE ','
#define SEPARATOR_INPUT_FILE '|'

class BitcoinExchange {

private:
    std::map<std::list<int>, double> _data;
    
public:

    void print()const;
    ~BitcoinExchange();
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &toCopy);

    const std::map<std::list<int>, double>& get_map()const;
    BitcoinExchange &operator=(const BitcoinExchange &toCopy);
};

void parse_file(std::list<int> &t_array, double &value, std::stringstream &ss, char separator);
bool is_valid_date(std::list<int> t_array);
double wrapper_strtod(const std::string& str);
int wrapper_strtol(const std::string& str);

#endif