#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
#include <algorithm>

void first_sort_pair(std::list<int> &my_list)
{
    std::list<int>::iterator a = my_list.begin();//first comp
    std::list<int>::iterator b;//last comp

    for (;a != my_list.end(); a++)
    {
        b = a;
        b++;
        if (b == my_list.end())
            break;
        if (*a > *b)//swap
            iter_swap(a, b);
        a = b;
    }
}

double pow2(int n)
{
    double result = 1;
    for(; n > 0; n--)
        result *= 2;
    return (result);
}

bool increment_iterator(std::list<int>::iterator &it, const std::list<int>::iterator &ite, unsigned int step)
{
    if (it == ite)
        return (false);
    for (; step > 0; step--)
    {
        it++;
        if (it == ite)
            return (false);
    }
    return (true);
}

void sort_pair_recursion(std::list<int> &my_list, unsigned int &recursion)
{
    std::list<int>::iterator ite = my_list.end();
    std::list<int>::iterator a = my_list.begin();//missed swap a and b
    std::list<int>::iterator b;
    if (pow2(recursion) > my_list.size() / 2)//break when you can´t make an other bigger than last
        {--recursion; return;}
    for(; a != ite; a++)
    {
        if (!increment_iterator(a, ite, static_cast<unsigned int> (pow2(recursion)) - 1))
            return (sort_pair_recursion(my_list, ++recursion));
        b = a;
        if (!increment_iterator(b, ite, static_cast<unsigned int> (pow2(recursion))))
            return (sort_pair_recursion(my_list, ++recursion));
        if (*a > *b)
        {
            for (unsigned int i = pow2(recursion) - 1; i > 0; i--, a--, b--)
                iter_swap(a, b);
            iter_swap(a, b);
            a = b;
        }
        if (!increment_iterator(a, ite, static_cast<unsigned int> (pow2(recursion)) - 1))
            return (sort_pair_recursion(my_list, ++recursion));
    }
    return (sort_pair_recursion(my_list, ++recursion));
}

std::list<int>::iterator next(std::list<int>::iterator it, int step)
{
    std::list<int>::iterator to_return = it;
    std::advance(to_return, step);
    return (to_return);
}

//Suite of jacob Stal Jn = J(n-1) + 2J(n-2)
//
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
    return (to_return);
}

std::list<int> creation_list(std::list<int> &my_list, unsigned int number_in_pair)
{//Je dois creer la main, donc prendre le nombre de pair et recuperer
    unsigned int comp_size = my_list.size();
    bool pair = false;
    std::list<int> to_return;
    std::list<int>::iterator buff;
    std::list<int>::iterator it_return = to_return.begin();
    std::list<int>::iterator it = my_list.begin();
    buff = next(it, number_in_pair * 2);
    to_return.insert(it_return, it, buff);//Ici j'insert dans ma list a return, depuis le debut, l'iterateur de ma list passe en param jusqu a la 2 * le numbre de pair
    my_list.erase(it, buff);
    it = buff;
    comp_size -= number_in_pair * 2; 
    for (; it != my_list.end();)//tant que my_list n'est pas parcourut// faire la securite de std::advance pour eviter l'overflow
    {
        if (comp_size < number_in_pair)//security for advance
            break;
        if (pair == true)
        {
            buff = next(it, number_in_pair);
            to_return.insert(it_return, it, buff);//j'insert it_return qui s'incremente avec les appels recrusifs de insert, 
            my_list.erase(it, buff);
            it = buff;
            pair = false;
        }
        else
        {
            pair = true;
            std::advance(it, number_in_pair);
        }
        comp_size -= number_in_pair;
    }
    return (to_return);
}

std::list<int> reverse_sort_pair_recursion(std::list<int> &my_list, unsigned int &recursion)
{   //la fonction va creer un list main qui sera passe en param sur tout les appels recursifs a la toute fin a la recursion 0 je return la liste triee
    //my list dans les fonction recursif doit etre la pend
    //faire en sorte qu'une list soit cree que l'on passe en param des appels recursif de ma fonction en decrementant ma var "recursion",
    //On fais aussi de la recherche dichotomique avec les paires
    std::list<int> main = creation_list(my_list, pow2(recursion));
    std::list<int>::iterator it = main.begin();
    std::list<int>::iterator it_pend = my_list.begin();
    std::advance(it_pend, pow2(recursion));
    std::deque<unsigned int> jacob_number = sequence_jacob_stahl(my_list.size() / pow2(recursion));
    unsigned int b = 2;//it's who start the Pend
    unsigned int binairy_size;
    for (; my_list.size() >= pow2(recursion); )//Je fini quand ma Pend n'a plut assez de nombre
    {
        binairy_size = (pow2(recursion) * (b - 1) + pow2(recursion));
        //la size de ma lsit est donc egal (pow2(recursion) * (b - 1) + pow2(recursion))
        //jacob_number[i] - 1

        for (unsigned int i = binairy_size / 2; i != binairy_size && i != 0;)//!! faire la recherche dichotomique
        {
            std::advance(it, i);
            if (*it <= my_list)//iterateur de ma list est < ou > 
            else
            
        }
        main.insert();
    }
}

void sort_pair(std::list<int> &my_list)
{//On utuilise la suite de jacob sthal car elle suit la regle de la recherche dichotomique
    first_sort_pair(my_list);
    for (std::list<int>::const_iterator it = my_list.begin(); it != my_list.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    unsigned int recursion = 1;
    sort_pair_recursion(my_list, recursion);
    std::cout << "recursion: " << recursion << std::endl;
    for (std::list<int>::const_iterator it = my_list.begin(); it != my_list.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    recursion = 1;
    if (pow2(recursion) * 2 >= my_list.size())
        recursion--;
    std::list<int> main = creation_list(my_list, pow2(recursion));
    std::cout << "Pend: ";
    for (std::list<int>::const_iterator it = my_list.begin(); it != my_list.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "Main: ";
    for (std::list<int>::const_iterator it = main.begin(); it != main.end(); it++)
        std::cout << *it << " ";
    //reverse_sort_pair_recursion(my_list, recursion);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)//check, is there everything to sort
        {std::cout << "Nothing to sort !" << std::endl; return (0);}
    std::deque<std::string> parse_deque(argv + 1, argv + argc);

    for (int i = 0; i < argc - 1; i++)//parse for nothing other number
    {
        for (size_t l = 0; l < parse_deque[i].length(); l++)
        {
            if (!isdigit(parse_deque[i][l]) && !(isspace(parse_deque[i][l])))
                {std::cout << "Error: " << parse_deque[i][l] << std::endl ;return (1);}
        }
    }

    std::list<int> my_list;
    for (int i = parse_deque.size() - 1; i >= 0; i--)//fill my struct with number of argv
    {
        errno = 0;
        long int number = strtol(parse_deque[i].c_str(), NULL, 10);
        if (errno != 0)
            {std::perror("Error: strtol failed "); return (1);}
        my_list.push_front(number);
    }

    std::deque<int> my_deque(my_list.begin(), my_list.end());

    sort_pair(my_list);

/*
    MyArray<std::deque<int>> PmergeDeque;
    MyArray<std::list<int>>  PmergeList;
*/
    return (0);

}