#include "PmergeMe.hpp"

int main(int argc, const char *argv[])
{
    if (argc < 2)
        {std::cout << "Not enough information" << std::endl; return (1);}

    try
    {
        {//This scope is for filling the container. I am not sure exactly how my CPU handles it,
        //but I believe it populates the cache, making the next pass faster than the previous one
            struct timespec time;
            Pmerge<std::vector<unsigned int> > container;
            
            if (clock_gettime(CLOCK_MONOTONIC, &time))
                throw(std::invalid_argument("Error: gettime"));
            container.fill(argc - 1, argv + 1);
            std::cout << "Before : "; container.display(); std::cout << std::endl;
            container.sort();
            std::cout << "After : "; container.display(); std::cout << std::endl;
        }

        {
            struct timespec time;
            Pmerge<std::vector<unsigned int> > container;

            if (clock_gettime(CLOCK_MONOTONIC, &time))
                throw(std::invalid_argument("Error: gettime"));
            container.fill(argc - 1, argv + 1);
            container.sort();
            print_nano_seconde_timespec<std::vector<unsigned int> >(container.size(), time);
            
        }
        
        {//This scope is for filling the container. I am not sure exactly how my CPU handles it,
        //but I believe it populates the cache, making the next pass faster than the previous one
            struct timespec time;
            Pmerge<std::deque<unsigned int> > container;
            
            if (clock_gettime(CLOCK_MONOTONIC, &time))
                throw(std::invalid_argument("Error: gettime"));
            container.fill(argc - 1, argv + 1);
            container.sort();
        }

        {
            struct timespec time;
            Pmerge<std::deque<unsigned int> > container;

            if (clock_gettime(CLOCK_MONOTONIC, &time))
                throw(std::invalid_argument("Error: gettime"));
            container.fill(argc - 1, argv + 1);
            container.sort();
            print_nano_seconde_timespec<std::deque<unsigned int> >(container.size(), time);
        }
    }
    catch(const std::exception &Exception){
        std::cout << Exception.what() << std::endl;}
    return (0);
}
