#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <stdexcept>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <errno.h>
#include <math.h>

class MyDeque: public std::deque<unsigned int> {

private:
    void sort_pair(unsigned int &recursion);
    void reverse_sort_pair(int recursion);

public:
    MyDeque &operator=(const MyDeque &to_copy);
    ~MyDeque();
    MyDeque();
    MyDeque(const MyDeque &to_copy);
    void fill(int argc, const char *argv[]);
    void sort();
};

#endif