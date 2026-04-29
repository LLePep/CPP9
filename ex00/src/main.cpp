#include "BitcoinExchange.hpp"

static void print_change_bitcoin(std::list<int> t_array, double bitcoin_number, double bitcoin_change)
{
    std::list<int>::const_iterator it = t_array.begin();
    std::cout << *it++ << "-" << std::setfill('0') << std::setw(2) << *it++ << "-" << std::setfill('0') << std::setw(2) << *it++ << " => "
    << bitcoin_number << " = " << bitcoin_change * bitcoin_number << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)//Wrong number of argument
    {
        std::cout << "Wrong number of param !" << std::endl;
        return (1);}
    try
    {
        BitcoinExchange data_change;
        std::ifstream ifs;
        ifs.open(argv[1], std::ifstream::in);
        if (!ifs.is_open())//check file the opener
            throw std::runtime_error("Open Fail: " + std::string(argv[1]));
        std::string str;
        std::getline(ifs, str);
        if (str != "date | value")//first line of my file .txt
            throw std::invalid_argument("Invalid base.");
        while (std::getline(ifs, str))
        {
            std::list<int> t_array;
            std::stringstream ss(str);
            double value;

            try{
                parse_file(t_array, value, ss, SEPARATOR_INPUT_FILE);
                if (value < 0)
                    throw std::invalid_argument("not a positive number.");
                else if (value > 1000)
                    throw std::invalid_argument("too large a number");
                std::map<std::list<int>, double>::const_iterator it = data_change.get_map().upper_bound(t_array);
                if (it == data_change.get_map().begin())
                    throw std::invalid_argument("date to old");
                else
                    print_change_bitcoin(t_array, value, (--it)->second);
            }
            catch(const std::exception &Exception){
                std::cout << "Error: " << Exception.what() << std::endl;}
        }
    }
    catch(const std::exception &Exception){
        std::cout << "Error: " << Exception.what() << std::endl;}
    return (0);
}
