/************************************************************************************************************************************************************
 * @file Ex_10_20.cpp
 * @brief Exercise 10.20: The library defines an algorithm named count_if. Like find_if,this function takes a pair of iterators
 *        denoting an input range and a predicate that it applies to each element in the given range. count_if returns a count
 *        of how often the predicate is true. Use count_if to rewrite the portion of our program that counted how many words
 *        are greater than length 6.
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void biggies(std::vector<std::string> &words);
void elimDups(std::vector<std::string> &words);

int main(){
    std::vector<std::string> wordlst;
    std::cout << "Enter the list of words : " << std::endl;
    std::string word;
    while(std::cin >> word){
        wordlst.push_back(word);
    }

    biggies(wordlst);
    return 0;
}

void biggies(std::vector<std::string> &words){
    
    // sorts the list in dict order, removes dup words and sorts by length by preserving dict order
    elimDups(words);

    // code to count the number of words greater than 6
    std::string::size_type sz = 6;
    auto count = std::count_if(words.begin(), words.end(), [sz](const std::string &str){ return str.size() > sz; });
    std::cout << "\nthere are " << count << " words greater than " << sz << " letters" << std::endl;

    //  code to partition the list wiht element whose size is greater than sz preceding the rest with original order preserved
    auto endOfMatches = std::stable_partition(words.begin(), words.end(), [sz](std::string &str){ return str.size() > sz ;});
    std::cout << "\nwords bigger than " << sz << " letter" << std::endl;
    std::for_each(words.begin(), endOfMatches, [](std::string &str){ std::cout << str << " " ;});
    
    return;
}

void elimDups(std::vector<std::string> &words){

    // code to sort the list
    std::sort(words.begin(), words.end());
    std::cout << "\nsorted list of words with duplicates : " << std::endl;
    std::for_each(words.begin(), words.end(), [](std::string &str){ std::cout << str << " ";});
    std::cout << std::endl;

    // code to eliminate dups
    auto endUnique = std::unique(words.begin(), words.end());
    words.erase(endUnique, words.end());  //    erases the duplicate words
    std::cout << "\nSorted list of unique words : " << std::endl;
    std::for_each(words.begin(), words.end(), [](std::string &str){std::cout << str << " "; });
    std::cout << std::endl;

    // code to sort the list based on length preserving alphabetical order
    std::stable_sort(words.begin(), words.end(), [](const std::string &lhs,const std::string &rhs){ return lhs.size() < rhs.size(); });
    std::cout << "\nsorted list of words by length : " << std::endl; 
    std::for_each(words.begin(), words.end(), [](std::string &str){ std::cout << str << " ";});
    std::cout << std::endl;

    return;
}