#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {

private:
    std::map<std::array<int, 3>, double> _data;
    BitcoinExchange();

public:
    ~BitcoinExchange();
    BitcoinExchange(std::string& file);
    BitcoinExchange(const BitcoinExchange &toCopy);

    BitcoinExchange &operator=(const BitcoinExchange &toCopy);

};

#endif