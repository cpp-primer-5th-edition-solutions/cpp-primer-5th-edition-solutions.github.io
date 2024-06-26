/************************************************************************************************************************************************************
 * @file Ex_9_28.cppExercise 9.28: Write a function that takes a forward_list<string> and two additional string arguments. 
 *       The function should find the first string and insert the second immediately following the first. If the first string
 *       is not found, then insert the second string at the end of the list.
 * @brief 
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <forward_list>

void insert_word(std::forward_list<std::string> &flst, const std::string &sought, const std::string &new_word);
int main(){
    std::forward_list<std::string> flist{"one","two","three","four"};
    insert_word(flist, "one", "hello");
    for( auto s : flist){
        std::cout << s << " ";
    }
    
    return 0;
}

void insert_word(std::forward_list<std::string> &flst, const std::string &sought, const std::string &new_word){
    auto prev = flst.before_begin();        //  this iterator is imporatant without which, won't be able insert at the end
    auto curr = flst.begin();               //  as forward_list doesn't support decrement, last = flst.end() - 1, is not possible
    while( curr != flst.end()){             //  so, to insert after the last element we need to iterate through the flst.
        if(*curr == sought){
            flst.insert_after(curr, new_word);
            return;
        }else{
            prev = curr;
            ++curr;
        }
    }
    flst.insert_after(prev, new_word);
}
