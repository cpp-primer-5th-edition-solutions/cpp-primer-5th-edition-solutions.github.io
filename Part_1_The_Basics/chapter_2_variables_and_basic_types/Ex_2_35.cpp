/*  Exercise 2.35: Determine the types deduced in each of the following definitions. Once you’ve figured out the types, 
    write a program to see whether you were correct. */

#include <iostream>

int main(){
    const int i = 42;
    auto j = i;                             //  j is int with 42, as top level const i is ignored
    const auto &k = i;                      //  k is a reference to const, though un-necessart declaration of const
    auto *p = &i;                           //  p is const int *
    const auto j2 = i, &k2 = i;             //  j2 is const int, k2 is const int &, ( const is must otherwise j2 will be 
                                            //    int and k2 will const int & )

    std::cout << "i = " << i << "\n" 
              << "j = " << j << "\n"
              << "k = " << k << "\n"
              << "*p = " << *p << "\n"
              << "j2 = " << j2 << std::endl
              << "k2 = " << k2 << std::endl;     
    return 0;
}    