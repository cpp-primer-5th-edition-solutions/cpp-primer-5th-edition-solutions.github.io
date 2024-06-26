/************************************************************************************************************************************************************
 * @file Ex_1_18.cpp
 * @brief Exercise 1.18: Compile and run the program from this section giving it only equal values as input. Run it 
 * again giving it values in which no number is repeated.
 * @date 2024-03-14
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
int main()
{
    // currVal is the number we’re counting; we’ll read new values into val 
    int currVal = 0,
    val = 0;
    // read first number and ensure that we have data to process
    if (std::cin >> currVal) {
        int cnt = 1; // store the count for the current value we’re processing
        while (std::cin >> val) { // read the remaining numbers
            if (val == currVal) // if the values are the same
                ++cnt; // add 1 to cnt
            else
            { // otherwise, print the count for the previous value
                std::cout << currVal << " occurs "
                          << cnt << " times" << std::endl;
                currVal = val; // remember the new value
                cnt = 1; // reset the counter
            }
        } // while loop ends here
          // remember to print the count for the last value in the file
        std::cout << currVal << " occurs "
                  << cnt << " times" << std::endl;
    } // outermost if statement ends here 
    return 0;
}

// equal values : <value> occurs <cnt> times
/* unique numbers :
   <value1> occurs 1 times
   <value2> occurs 1 times
   <value3> occurs 1 times
   <valuen> occurs 1 times
*/