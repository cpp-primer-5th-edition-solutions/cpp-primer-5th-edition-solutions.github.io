/************************************************************************************************************************************************************
 * @file Ex_16_34.cpp
 * @brief Exercise 16.34: Given only the following code, explain whether each of these calls is legal. If so, what is
 *  the type of T? If not, why not?
 * template <class T> int compare(const T&, const T&);
 * (a) compare("hi", "world"); (b) compare("bye", "dad");
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * template <class T> int compare(const T&, const T&);
 * (a) compare("hi", "world");  // illegal : as the parameter are reference of the same template parameter type, both arguments should be same type,
 *                              //          but 1st argument const char [3], 2nd argument is const char [6], as for arrays
 *                              //          as the size is part of the type, arguments are not of same type                   
 * (b) compare("bye", "dad");   // ok : both arguments are of same type const char [4].
 * 
 *************************************************************************************************************************************************************/

#include <iostream>

template <typename T>
bool compare(const T &arr1, const T & arr2) {
    return std::size(arr1) == std::size(arr2);
}

int main() {
    std::cout << "compare(\"hi\", \"world\") : " << compare("bye","dad") << std::endl; 
}