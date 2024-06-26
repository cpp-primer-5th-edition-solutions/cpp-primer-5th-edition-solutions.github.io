/************************************************************************************************************************************************************
 * @file Ex_9_45.cpp
 * @brief Exercise 9.45: Write a funtion that takes a string representing a name and two other strings representing a prefix, 
 *        such as “Mr.” or “Ms.” and a suffix, such as “Jr.” or “III”. Using iterators and the insert and append functions, 
 *        generate and return a new string with the suffix and prefix added to the given name.
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

std::string addTitle(const std::string &s, const std::string &prefix, const std::string &suffix = std::string()){
    std::string res(s);
    std::string space(" ");
    if(!prefix.empty()){
        res.insert(res.begin(), space.cbegin(), space.cend());  //  adds space before name
        res.insert(res.begin(),prefix.cbegin(), prefix.cend()); //  adds title before space
    }

    if(!suffix.empty()){
        res.append(space + suffix);     
    }

    return res;
}

int main(){
    std::string name1("Sherlock"), name2("Tony"), name3("Charles");
    std::vector<std::string> prefix{"Mr","Mrs"};
    std::vector<std::string> suffix{"Jr","III"}; 
    std::cout << addTitle(name1, prefix[1], suffix[1]) << std::endl;
    std::cout << addTitle(name2, "", suffix[0]) << std::endl;
    std::cout << addTitle(name3, prefix[0], "") << std::endl;

}