#include "PmergeMe.hpp"

MyDeque::MyDeque(){}

MyDeque::~MyDeque(){}

MyDeque::MyDeque(const MyDeque &to_copy): std::deque<unsigned int>(to_copy) {}

MyDeque &MyDeque::operator=(const MyDeque &to_copy)
{
    if (this == &to_copy)
        return (*this);
    std::deque<unsigned int>::operator=(to_copy);
    return (*this);
}

void MyDeque::fill(int argc, const char *argv[])
{
    int i = 0;
    long int number;
    while (argc > i)
    {
        for (size_t l = 0; argv[i][l] != '\0'; l++)
        {
            if (!isdigit(argv[i][l]))
                {
                    throw std::invalid_argument("");//!!! here
                }
        }
        errno = 0;
        number = strtol(argv[i], NULL, 10);
        if (errno != 0)
            {std::perror("Error: strtol failed "); throw std::invalid_argument("");}
        this->push_back(number);
        i++;
    }
}

static unsigned int pow2(int n)
{
    double result = 1;
    for(; n > 0; n--)
        result *= 2;
    return (result);
}

void MyDeque::sort_pair(unsigned int &recursion)
{
    unsigned int block_size = pow2(recursion);
    unsigned int pair_size = block_size * 2;
    if (pair_size > this->size())
        {--recursion; return;}
    for (unsigned int a = 0; a + pair_size <= this->size(); a += pair_size)
    {
        if ((*this)[a + (block_size - 1)] > (*this)[a + (pair_size - 1)])
        {
            for (unsigned int i = 0; i < block_size; i++)
                std::swap((*this)[a + i], (*this)[a + i + block_size]);
        }
    }
    return (sort_pair(++recursion));
}

void creation_main(std::deque<unsigned int> &main_index, MyDeque &old, unsigned int block_size)
{
    MyDeque to_return;
    for (unsigned int i = 0; i != main_index.size(); i++)
    {
        for (unsigned int k = 0; k < block_size; k++)
        {
            if (main_index[i] + k < old.size())
                to_return.push_back(old[main_index[i] + k]);
        }
    }
    old = to_return;
}

std::deque<unsigned int> sequence_jacob_stahl(unsigned int size)
{
    std::deque<unsigned int> to_return;

    unsigned int j = 0;//n-2
    unsigned int k = 1;//n-1
    unsigned int result = 0;
    for (; result < size;)//search the bigger jacob number than size and return n-1 
    {
        result = k + 2 * j;
        j = k;
        k = result;
        to_return.push_back(result);
    }
    to_return.back() = size;
    return (to_return);
}

std::deque<unsigned int> creation_main_index(unsigned int total_size, unsigned int block_size)
{
    std::deque<unsigned int> to_return;
    to_return.push_back(0);
    for (unsigned int i = 1; total_size > i * block_size; i += 2)
        to_return.push_back(i * block_size);
    return (to_return);
}

std::deque<unsigned int> creation_pend_index(unsigned int total_size, unsigned int block_size)
{
    std::deque<unsigned int> to_return;
    for (unsigned int i = 2; total_size > i * block_size; i += 2)
        to_return.push_back(i * block_size);
    return (to_return);
}

void binairy_search(unsigned int block_size, unsigned int index_pend, std::deque<unsigned int> &main_index, MyDeque &main)
{
    unsigned int value = main[index_pend + (block_size - 1)];

    unsigned int size = 0;
    unsigned int partner_index = index_pend + block_size;
    if (partner_index == main.size())//check if there is an partner block for index_pend
        size = main_index.size();
    else
    {
        while (size < main_index.size() && main_index[size] != partner_index)
            size++;
    }
    
    unsigned int start = 0;
    unsigned int step = size / 2;
    while (size != start)
    {
        if (value > main[main_index[step] + block_size - 1])
            start = step + 1;
        else
            size = step;
        step = (start + size) /2;
    }
    main_index.insert(main_index.begin() + start, index_pend);
}

void MyDeque::reverse_sort_pair(int recursion)
{
    while (recursion >= 0)
    {
        unsigned int block_size = pow2(recursion);
        unsigned int pair_size = block_size * 2;

        std::deque<unsigned int> jacob_suite = sequence_jacob_stahl(round(static_cast<double> (this->size()) / static_cast<double> (pair_size)));

        std::deque<unsigned int> main_index = creation_main_index(this->size(), block_size);
        std::deque<unsigned int> pend_index = creation_pend_index(this->size(), block_size);
        
        //calcul the sequence of jacob stahl with a number of element and give a suite with match
        unsigned int i = 1;
        
        while (i < jacob_suite.size())
        {
            unsigned int k = jacob_suite[i - 1];
            for (unsigned int index_jacob = jacob_suite[i]; index_jacob > k; index_jacob--)//For followinf the sequence of jacob_suite
            {
                unsigned int index_pend = pend_index[index_jacob - 2];
                binairy_search(block_size, index_pend, main_index, *this);
            }
            i++;
        }

        creation_main(main_index, *this, block_size);
        --recursion;
    }
    return ;
}

void MyDeque::sort()
{
    unsigned int recursion = 0;
    this->sort_pair(recursion);
    std::cout << "First sort:";
    for (std::deque<unsigned int>::const_iterator it = this->begin(); it != this->end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    this->reverse_sort_pair(recursion);
    std::cout << "Finish sort:";
    for (std::deque<unsigned int>::const_iterator it = this->begin(); it != this->end(); it++)
    {
        std::cout << " " << *it;
    }
    //this->reverse_sort_pair(recursion);
}
