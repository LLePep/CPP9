#include "PmergeMe.hpp"

int main(int argc, const char *argv[])
{
    if (argc < 2)
        return (1);
    {
        MyDeque<std::vector<unsigned int> > container;
        try{
            container.fill(argc - 1, argv + 1);
            container.sort();    
        }
        catch(const std::exception &Exception){
            std::cerr << Exception.what() << std::endl;}

    }
    return (0);
}
