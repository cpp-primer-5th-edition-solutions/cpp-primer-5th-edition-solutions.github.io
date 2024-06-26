/************************************************************************************************************************************************************
 * @file Ex_12_28.cpp
 * @brief Exercise 12.28: Write a program to implement text queries without defining classes to manage the data. Your program 
 * should take a file and interact with a user to query for words in that file. Use vector, map, and set containers to hold the
 * data for the file and to generate the results for the queries.
 * @date 2024-01-19
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>

int main(){
    std::ifstream ifile("text.txt");
    if(!ifile){
        std::cerr << "Unable to open file" << std::endl;
        return -1;
    }
    
    typedef std::vector<std::string>::size_type index_type;

    std::vector<std::string> text;
    std::map<std::string, std::set<index_type>> word_map;

    std::string line;
    index_type line_no = 0;
    while(getline(ifile, line)){
        text.push_back(line);
        std::istringstream linestrm(line);
        std::string word;
        while(linestrm >> word){
            word_map[word].insert(line_no);
        }
        ++line_no;
        line.clear();
    }

    std::cout << "\nEnter the word to search or q to quit : ";
    std::string srch_word;
    
    while(true){
        if(!(std::cin >> srch_word) || srch_word == "q" ){
            break;
        }
        auto result = word_map.find(srch_word);
        if(result != word_map.end()){
            std::cout << srch_word << " is found in the following lines.....\n" << std::endl;
            for(auto iter = result->second.cbegin(); iter != result->second.cend(); ++iter){
                std::cout << "[ " << *iter << " ]" << text[*iter] << std::endl;
            }
        }
        std::cout << "Enter the word to search or q to quit : ";
    }

    return 0;    
}