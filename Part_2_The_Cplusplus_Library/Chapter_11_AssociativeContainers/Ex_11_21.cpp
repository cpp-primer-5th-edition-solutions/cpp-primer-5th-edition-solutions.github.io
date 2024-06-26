/************************************************************************************************************************************************************
 * @file Ex_11_21.cpp
 * @brief Exercise 11.21: Assuming word_count is a map from string to size_t and word is a string, explain the following
 *        loop: 
 *        while (cin >> word) 
 *              ++word_count.insert({word, 0}).first->second;
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

++(((word_count.insert({word,0})).first)->second)

- word_count calls its insert member with brace initialised argument of type pair, which adds "word" as the key and the value as 0 
and returns an object of pair type containing first element as iter to the element in map and bool indicated whether insertion 
successfull or not
   - Then the pair type first member is called using . operator, which is iterator to the element inserted or already
     present in the map 
   - element in the map is a pair containing key and its value
   - so we use -> operator to fetch the second member that is the value contained in the element 
   - ++ increments the value in the element atlast 
   