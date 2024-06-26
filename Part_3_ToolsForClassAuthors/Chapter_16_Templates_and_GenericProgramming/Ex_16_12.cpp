/************************************************************************************************************************************************************
 * @file Ex_16_12.cpp
 * @brief Exercise 16.12: Write your own version of the Blob and BlobPtr templates. including the various const members
 * that were not shown in the text.
 * @date 2024-02-11
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include "BlobTemplate.cpp"
#include "BlobPtrTemplate.cpp"
#include <fstream>

int main() {
    std::ifstream ifile("text.txt");

    if(!ifile) {
        std::cout << "Unable to open file" << std::endl;
        return -1;
    }

    typedef Blob<std::string> StrBlob;
    StrBlob b1;
    std::string line;
    while(getline(ifile,line)) {
        b1.push_back(line);
    }

    for (auto iter = b1.begin(); iter != b1.end(); ++iter) {
        std::cout << *iter << std::endl;
    }

    return 0;
}