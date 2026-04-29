static unsigned int pow2(int n)
{
    double result = 1;
    for(; n > 0; n--)
        result *= 2;
    return (result);
}

template <typename T>
std::string get_container_name();

template <>
inline std::string get_container_name<std::vector<unsigned int> >() { 
    return "std::vector<unsigned int> "; 
}

template <>
inline std::string get_container_name<std::deque<unsigned int> >() { 
    return "std::deque<unsigned int> "; 
}

template <typename T>
Pmerge<T>::Pmerge(){}

template <typename T>
Pmerge<T>::~Pmerge(){}

template <typename T>
Pmerge<T>::Pmerge(const Pmerge &to_copy): T(to_copy) {}

template <typename T>
Pmerge<T> &Pmerge<T>::operator=(const Pmerge &to_copy)
{
    if (this == &to_copy)
        return (*this);
    T::operator=(to_copy);
    return (*this);
}

template <typename T>
void Pmerge<T>::fill(int argc, const char *argv[])
{
    int i = 0;
    long int number;
    while (argc > i)
    {
        for (size_t l = 0; argv[i][l] != '\0'; l++)
        {
            if (!isdigit(argv[i][l]))
                {
                    throw std::invalid_argument("Error: digit");
                }
        }
        errno = 0;
        number = strtol(argv[i], NULL, 10);
        if (errno != 0)
            {std::perror("Error: strtol failed "); throw std::invalid_argument("Error: errno");}
        this->push_back(number);
        i++;
    }
}

template <typename T>
void Pmerge<T>::sort_pair(unsigned int &recursion)
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

template <typename T>
void creation_main(T &main_index, Pmerge<T> &old, unsigned int block_size)
{
    Pmerge<T> to_return;
    unsigned int i = 0;
    
    for (; i != main_index.size(); i++)
    {
        for (unsigned int k = 0; k < block_size; k++)
        {
            if (main_index[i] + k < old.size())
                to_return.push_back(old[main_index[i] + k]);
        }
    }
    if (i * block_size < old.size())
    {
        for (unsigned int n = 0; i * block_size + n < old.size(); n++)
            to_return.push_back(old[i * block_size + n]);
    }
    old = to_return;
}

template <typename T>
T sequence_jacob_stahl(unsigned int size)
{
    T to_return;

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

template <typename T>
T creation_main_index(unsigned int total_size, unsigned int block_size)
{
    T to_return;
    to_return.push_back(0);
    for (unsigned int i = 1; total_size > i * block_size; i += 2)
        to_return.push_back(i * block_size);
    return (to_return);
}

template <typename T>
T creation_pend_index(unsigned int total_size, unsigned int block_size)
{
    T to_return;
    for (unsigned int i = 2; total_size > i * block_size; i += 2)
        to_return.push_back(i * block_size);
    return (to_return);
}

template <typename T>
void binairy_search(unsigned int block_size, unsigned int index_pend, T &main_index, Pmerge<T> &main)
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

template <typename T>
void Pmerge<T>::reverse_sort_pair(int recursion)
{
    while (recursion >= 0)
    {
        unsigned int block_size = pow2(recursion);
        unsigned int pair_size = block_size * 2;

        T jacob_suite = sequence_jacob_stahl<T>(round(static_cast<double> (this->size()) / static_cast<double> (pair_size)));

        T main_index = creation_main_index<T>(this->size(), block_size);
        T pend_index = creation_pend_index<T>(this->size(), block_size);
        
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

template <typename T>
void Pmerge<T>::sort()
{
    unsigned int recursion = 0;
    this->sort_pair(recursion);
    this->reverse_sort_pair(recursion);
}

template <typename T>
void Pmerge<T>::display()
{
    for (typename T::const_iterator it = this->begin(); it != this->end(); it++)
        std::cout << *it << " ";
}

template <typename T>
void Pmerge<T>::check()
{
    for (unsigned int i = 0; i < this->size() - 1; i++)
    {
        if ((*this)[i] > (*this)[i + 1])
            {std::cout << "Not sort: " << (*this)[i] << " "<< (*this)[i + 1] << std::endl; return;}
    }
    std::cout << "List sorted" << std::endl;
}

template <typename T>
void print_nano_seconde_timespec(unsigned int size, struct timespec time)
{
    struct timespec time_comp;
    
    if (clock_gettime(CLOCK_MONOTONIC, &time_comp))
        return ;

    long seconde = time_comp.tv_sec - time.tv_sec;
    long nanoseconde = time_comp.tv_nsec - time.tv_nsec;
    
    if (nanoseconde < 0)//adjust the calcul for no negat
    {
        seconde -= 1;
        nanoseconde += 1000000000;
    }
    
    if (seconde == 0 && nanoseconde < 100000)// nanoseconde < 100us
        std::cout << "Time to process a range of " << size << " elements with " << get_container_name<T>() << (seconde * 1000000000 + nanoseconde) << "ns" << std::endl;
    else if (seconde == 0 && nanoseconde < 100000000)// nanoseconde < 100ms
        std::cout << "Time to process a range of " << size << " elements with " << get_container_name<T>() << (seconde * 1000000 + nanoseconde/1000) << "us" << std::endl;
    else if (seconde < 100)//nanoseconde < 100s
        std::cout << "Time to process a range of " << size << " elements with " << get_container_name<T>() << (seconde * 1000 + nanoseconde/1000000) << "ms" << std::endl;
    else
        std::cout << "Time to process a range of " << size << " elements with " << get_container_name<T>() << (seconde + nanoseconde/1000000000) << "s" << std::endl;
}
