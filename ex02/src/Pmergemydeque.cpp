#include "PmergeMe.hpp"
#include <algorithm>

MyDeque::MyDeque(){}

MyDeque::~MyDeque(){}

MyDeque::MyDeque(const MyDeque &to_copy): std::deque<int>(to_copy) {}

MyDeque &MyDeque::operator=(const MyDeque &to_copy)
{
    if (this == &to_copy)
        return (*this);
    std::deque<int>::operator=(to_copy);
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
                    throw std::invalid_argument("");//
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

MyDeque creation_main(MyDeque &old, unsigned int &recursion)
{
    unsigned int size = old.size();
    MyDeque to_return;
    MyDeque stay;
    unsigned int block_size = pow2(recursion);
    unsigned int pair_size = block_size * 2;
    for (unsigned int i = 0; i < pair_size; i++)//push the first pair
        to_return.push_back(old[i]);
    for (unsigned int i = pair_size; i < size; i += pair_size)//compare the size with a number of pair
    {
        unsigned int k = 0;
        if (i + pair_size <= size)//check if it's a full pair or not
        {
            for (; k < block_size; k++)
                stay.push_back(old[i + k]);
            for (; k < pair_size; k++)
                to_return.push_back(old[i + k]);
        }
        else
        {
            for (; i + k < size; k++)
                stay.push_back(old[i + k]);
        }
    }
    old = stay;
    return (to_return);
}

std::deque<unsigned int> sequence_jacob_stahl(unsigned int size)
{
    if (size < 2)//creation o
    {
        if (size == 0)
            {std::deque<unsigned int> to_return(1, 0); return (to_return);}
        std::deque<unsigned> to_return(1, 1);
        return (to_return);
    }

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

/* unsigned int select_jacob_number(std::deque<unsigned int> jacob_suite, unsigned int number_pair, unsigned int i)
{
    if (jacob_suite[i] > number_pair)
        return (number_pair);
    return (jacob_suite[i]);
} */

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

void binairy_search(unsigned int block_size, unsigned int index_pend, std::deque<unsigned int> &main_index, MyDeque &main)//il nous faut la valeur la liste des index de la main et la main elle meme
{
    unsigned int value = main[index_pend];
    unsigned int limit_pend = index_pend + block_size;//j'ai donc l'index de pend bn qui est devant c'est a dire an
    unsigned int size = 0;
    while (main_index[size] != limit_pend)
        size++;
    unsigned int start = 0;
    unsigned int i = start + (start + size) / 2;
    while (start != size)
    {
        if (value > main_index[i])
            start = i + 1;
        else
            size = i;
        i = start + (start + size) / 2;
    }
    main_index.insert(main_index.begin() + start, index_pend);
}

void MyDeque::reverse_sort_pair(MyDeque &main, unsigned int recursion)
{//continuer avec la methode des index, ne pas oublier les reliquats
    if (recursion == 0) {return;}

    unsigned int block_size = pow2(recursion);
    unsigned int pair_size = block_size * 2;

    if (pair_size >= main.size())//Nothing to sort
        return (reverse_sort_pair(main, recursion - 1));
    
    std::deque<unsigned int> jacob_suite = sequence_jacob_stahl(main.size() / pair_size);//faire en sorte que les /2 sont >; cas "5 6 7 8 10 12 3 15 1 18 3 19"

    std::deque<unsigned int> main_index = creation_main_index(main.size(), block_size);
    std::deque<unsigned int> pend_index = creation_pend_index(main.size(), block_size);
    
    //calcul the sequence of jacob stahl with a number of element and give a suite with match
    unsigned int i = 1;
    
    while (i < jacob_suite.size())
    {
        unsigned int k = jacob_suite[i - 1];
        for (unsigned int index_jacob = jacob_suite[i]; index_jacob > k; index_jacob--)//element between index_jacob and index_jacob - 1
        {
            unsigned int index_pend = pend_index[index_jacob - 2];
            //retrouver l'elem de pend et l'elem de main dans main : main[index * pow2(recursion)];
            binairy_search(block_size, index_pend, main_index, main);
        }
        i++;
    }

/*     if (!old.empty())//check if pend isn't empty
    {} */
    return (reverse_sort_pair(main, --recursion));
}

void MyDeque::sort()
{
    unsigned int recursion = 0;
    this->sort_pair(recursion);
    for (std::deque<int>::const_iterator it = this->begin(); it != this->end(); it++)
    {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
    reverse_sort_pair(*this, recursion);
    //this->reverse_sort_pair(recursion);
}
