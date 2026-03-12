#include "BitcoinExchange.hpp"

bool BitcoinExchange::bixetile(std::string& input)
{

}

static bool is_valid_data(std::array<int, 3> t_array)
{

}

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(std::string& file)
{
    std::ifstream ifs;
    ifs.open("data.csv", std::ifstream::in);
    if (!ifs.is_open())//Open fail or Not 
        return ();//Error
    std::string str;
    while (std::getline(ifs, str))
    {
        std::array<int, 3> t_array;
        std::stringstream ss(str);
        std::string buff_str;
        double value;

        for (unsigned int i = 0; i < 3; i++)
        {
            try{
                std::getline(ss, buff_str, (i < 2 ? '-': ','));
                t_array[i] = stoi(buff_str, nullptr, 10);
            }
            catch(const std::exception &Exception){
                std::cerr << Exception.what() << std::endl;}
        
        }
        if (!is_valid_data(t_array))
            return ();//Error
        std::getline(ss, buff_str);
        try{
            value = stod(buff_str);}
        catch(const std::exception &Exception){
            std::cerr << Exception.what() << std::endl;}
        this->map.insert(std::pair<array<int, 3>, double> (t_array, value));
    }
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& toCopy)
{
    if (this == &toCopy)
        return (*this);
    this.map = toCopy.map;
    return (*this);
}
