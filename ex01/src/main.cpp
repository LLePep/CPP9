#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2){//Error
        std::cout << "This prog need of 2 argument !" << std::endl; return (1);}
    RPN<char> MyStack;
    try{
        std::string str = argv[1];
        MyStack.fill(str);
        std::cout << MyStack.calculate();}
    catch(const std::exception &Exception){
        std::cerr << "Error: " << Exception.what() << std::endl;}

    return (0);
}