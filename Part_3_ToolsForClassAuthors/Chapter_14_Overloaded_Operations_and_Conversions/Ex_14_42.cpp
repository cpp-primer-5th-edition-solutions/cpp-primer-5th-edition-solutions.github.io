/************************************************************************************************************************************************************
 * @file Ex_14_42.cpp
 * @brief Exercise 14.42: Using library function objects and adaptors, define an expression to
 * (a) Count the number of values that are greater than 1024
 * (b) Find the first string that is not equal to pooh
 * (c) Multiply all values by 2
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <utility>

using std::placeholders::_1;
int main(){
    std::vector<int> ivec{1023,1024,456,7865,3451,1900,456,987,999};
    int min = 2000;
    auto check = std::bind(std::greater_equal<int>(), _1, min);
    size_t count = std::count_if(ivec.begin(), ivec.end(), check);
    std::cout << count << std::endl;

    std::cout << "===============================================================" << std::endl;
    std::string word = "pooh";
    auto match = std::bind(std::not_equal_to<std::string>(), _1, word);
    std::vector<std::string> svec{"pooh","pooh","pooh","pool", "pooh","hello","pore","pond","serve"};
    auto first = std::find_if(svec.begin(), svec.end(), match);
    std::cout << *first << std::endl; 

    std::cout << "================================================================" << std::endl;
    int val = 2;
    std::vector<int> ivec2{1,3,5,7,9,2,4,6,8,10};
    auto multiply = std::bind(std::multiplies<int>(), _1, val);
    std::transform(ivec2.begin(), ivec2.end(), ivec2.begin(), multiply);
    for( auto n : ivec2){
        std::cout << n << " ";
    }

    return 0;
}
