/************************************************************************************************************************************************************
 * @file Ex_1_5.cpp
 * @brief Exercise 1.5: We wrote the output in one large statement. Rewrite the program to use a separate statement to
 * print each operand.
 * @date 2024-03-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <iostream>
int main()
{
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The product of " ;
    std::cout << v1 ;
    std::cout << " and " ;
    std::cout << v2;
    std::cout << " is ";
    std::cout << v1 * v2 << std::endl;
    return 0;
}