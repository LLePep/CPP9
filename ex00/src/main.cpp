#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)//Wrong number of argument
    {
        std::cout << "Wrong number of param !" << std::endl;
        return (1);}
    std::string file = argv[1];
    if (file.substr(file.size() - 4, 4) != ".csv")
        return (1);
    BitcoinExchange data_change(argv[1]);
    
    return (0);
}