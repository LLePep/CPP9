#include "BitcoinExchange.hpp"

static void print_change_bitcoin(std::vector<int> t_array, double bitcoin_number, double bitcoin_change)
{
    std::cout << t_array[0] << "-" << std::setfill('0') << std::setw(2) << t_array[1] << "-" << std::setfill('0') << std::setw(2) << t_array[2] << " => "
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
            std::vector<int> t_array(3);
            std::string buff_str;
            std::stringstream ss(str);
            double value;

            try{
                for (unsigned int i = 0; i < 3; i++)//set the date with wrapper of stol
                {
                    std::getline(ss, buff_str, (i < 2 ? '-': '|'));
                    t_array[i] = wrapper_strtol(buff_str);
                }
                if (!is_valid_date(t_array))//check if the date is valid
                {
                    std::stringstream ss_error;
                    ss_error << "bad input => " << t_array[0] << "-" << std::setfill('0') << std::setw(2) << t_array[1] << "-" << std::setfill('0') << std::setw(2) << t_array[2]; 
                    throw std::invalid_argument(ss_error.str());
                }
                std::getline(ss, buff_str);
                value = wrapper_strtod(buff_str);//buff_str
                std::map<std::vector<int>, double>::const_iterator it = data_change.get_map().upper_bound(t_array);
                if (it == data_change.get_map().begin())//!!! regarder les extremum
                    {print_change_bitcoin(t_array, value, it->second);}
                else
                    print_change_bitcoin(t_array, value, (--it)->second);
                }
            catch(const std::exception &Exception){
                std::cerr << "Error: " << Exception.what() << std::endl;}
        }
    }
    catch(const std::exception &Exception){
        std::cerr << "Error: " << Exception.what() << std::endl;}
    return (0);
}
