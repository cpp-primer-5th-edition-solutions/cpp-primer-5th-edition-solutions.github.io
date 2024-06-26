/*  Exercise 3.8: Rewrite the program in the first exercise, first using a while and again using a traditional for loop. 
    Which of the three approaches do you prefer and why?  */

#include <iostream>
#include <string>

int main(){
   std::cout << "Enter the word : " ;
   std::string word1;
   std::cin >> word1;
   std::string word2(word1);

   //   while to change every character in word to 'X'
   std::string::size_type index = 0;
   while( index <= word1.size() ){
        word1[index] = 'X';
        ++index;
   } 

    //  for loop changes every character in to 'X'
    for( std::string::size_type i = 0; i < word2.size(); ++i){
        word2[i] = 'X';
    } 

    std::cout << word1 << " " << word2 << std::endl;

    return 0;
}

/*  'range for' is preferrable as it is simple and straight-forward, it takes care of iteration through the sequence
    When it comes to accessing the sequence, both subscripting an empty sequence and out of bounds subcripting will result
    in to undefined behaviour which is taken care by the 'range for', where as in 'while' and traditional 'for' the developer
    have to be carefull */  