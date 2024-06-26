/************************************************************************************************************************************************************
 * @file Ex_9_21.cpp
 * @brief Exercise 9.21: Explain how the loop from page 345 that used the return from insert to add elements to a list would
 *        work if we inserted into a vector instead
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * @brief loop from page 345
 * list<string> lst; 
 * auto iter = lst.begin(); 
 * while (cin >> word) 
 *     iter = lst.insert(iter, word);
 *
 *************************************************************************************************************************************************************/

/**
 * It behaves the same way, as the container type doesn't matter in this case. Because insert() will always insert the word 
 * before the position pointed by the iter and returns iter referencing the word inserted
 * so next element will be inserted before the current element pointed by the iter
 * but other than the back insertion at any position in the vector will be slow unlike list, as all the elements might be moved
 * 
*/