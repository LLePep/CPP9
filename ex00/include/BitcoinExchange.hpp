#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <stdlib.h>
#include <stdexcept>
#include <iomanip>
#include <cerrno>

#define MONTH {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
#define DATA_BASE "data.csv"

class BitcoinExchange {

private:
    std::map<std::vector<int>, double> _data;
    
public:

    void print()const;
    ~BitcoinExchange();
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &toCopy);

    const std::map<std::vector<int>, double>& get_map()const;
    BitcoinExchange &operator=(const BitcoinExchange &toCopy);
};

bool is_valid_date(std::vector<int> t_array);
double wrapper_strtod(const std::string& str);
int wrapper_strtol(const std::string& str);

#endif