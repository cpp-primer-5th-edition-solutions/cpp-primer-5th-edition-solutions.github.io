/************************************************************************************************************************************************************
 * @file Ex_16_47.cpp
 * @brief Exercise 16.47: Write your own version of the flip function and test it by calling functions that have lvalue
 * and rvalue reference parameters.
 * @date 2024-02-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/


#include <iostream>

template <typename T>
T && forward(T &val) {
    return static_cast<T &&>(val);
}

void print1(int &&n, int &m) {
    std::cout << n << " " << ++m << std::endl;
}

void print2(int &n, int &&m) {
    std::cout << n << " " << ++m << std::endl;
}

template <typename T1, typename T2>
void flip(T1 &&val1, T2 &&val2) {
    print1(forward<T2>(val2) , forward<T1>(val1));   //  using custom forward()
    print1(std::forward<T2>(val2), std::forward<T1>(val1));  // using std::forward()

    print2(forward<T1>(val2), forward<T2>(val1));
    print2(std::forward<T1>(val2), std::forward<T2>(val1));
}



int main() {
    int n = 10, m = 20;
    flip(n,30);
    std::cout << n << " " << m << std::endl;
    std::cout << "============================" << std::endl;
    return 0;

}

/************************************************************************************************************************************************************
 * std::forward<T>(val)   //   returns an rvalue reference to explicit argument type.
 * if T is int &,  through reference collapsing in return, it returns int &
 * if T is int &&, through reference collapsing in return, it returns int &&
 * if T is int, it returns int &&
 * 
 * It is used, when we loose the original type when the function parameter is a rvalue reference to template parameter.
 * for ex : 
 *      template <typename T> void func1(T &&val) { func2(val); }
 * if lvalue is passed, T will lvalue reference, so val is lvalue reference,  so argument to func2 is lvalue reference same as first
 * if rvalue is passed, T will plain referred type,so val is rvalue ref, but argument to func2 is lvalue as any variable is a lvalue
 *      so in this case move() cannot be used as we are not moving the value
 *      so we use forward<T>(val), which  returns rvalue reference val, which is passed to func2.
 * 
 * (i)  if we pass const int, T is const int &, const is low-level,
 * (ii) if we pass const int &&, T is const int, const is low-level,
 * so when a function parameter is a rvalue reference to a template type parameter, by using std::forward<T> we can
 * preserve the type information of the call, (ie) in the above case   
 * (i) std::forward<T> returns const int &, same as original argument type
 * (ii) std::forward<T> returns const int &&, same as original argument type
 *************************************************************************************************************************************************************/