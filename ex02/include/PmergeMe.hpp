#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <stdexcept>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <errno.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

template <typename T>
class Pmerge: public T {

private:
    void sort_pair(unsigned int &recursion);
    void reverse_sort_pair(int recursion);

public:
    Pmerge &operator=(const Pmerge &to_copy);
    ~Pmerge();
    Pmerge();
    Pmerge(const Pmerge &to_copy);
    void display();
    void check();
    void fill(int argc, const char *argv[]);
    void sort();
};
void print_nano_seconde_timespec(unsigned int size, struct timespec time);

#include "PmergeMe.tpp"

#endif