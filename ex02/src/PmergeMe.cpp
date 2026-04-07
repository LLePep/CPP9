//faire les pairs

unsigned int pow2(int n)
{
    unsigned int to_return = 1;
    for (unsigned int i = 0; i < n ; i++)
        to_return *= 2;
    return (to_return);
}

int *search_list(const std::list<int> &my_list, unsigned int i,size_t size)
{
    if (i < size)//first part
    {
        std::list<int>::const_iterator it = my_list.begin();
        for (; i > 0; it++, i--)//i--
        {}
        return (&(*it));
    }
    else//last part
    {
        std::list<int>::const_iterator it = my_list.end();
        for (; i < size; it--, i++)//i++
        {}
        return (&(*it));
    }
}

void swap(int *a, int *b)
{
    int c = *b;

    *b = *a;
    *a = *c;
}

void first_sort_pair(std::list<int> my_list)
{
    unsigned int i = 0;
    size_t size = my_list.size();
    std::list<int>::const_itertor a = my_list.begin();//first comp
    std::list<int>::const_iterator b;//last comp

    for (;a != my_list.end(); a++)
    {
        b = a;
        b++;
        if (*a > *b)//swap
        {
            int buff = *a;
            *a = *b;
            *b = buff;
        }
        if (b == my_list.end())
            break;
        a++;
    }
}

void recursion_sort_pair(std::list<int> my_list, unsigned int jump)
{
    std::list<int> to_return;
    int i = 1;
/* 
    recursion 1: je dois comparer 0, 1; 2, 3; 4, 5; 
              2: 1, 3; 5, 7; 9, 11
              3: 3, 7; 13, 17
*/
    for ()
    {//je dois check si ma recursion est plausible
        if (my_list[(jump * i) - 1] > my_list[(jump * (i + 1)) - 1])//puissance de 2
            
        if (my_list.size() < recursion * i)
            break;
    }
    if ()
        sort_pair(to_return, jump * 2);
}

void truc()
{

}
