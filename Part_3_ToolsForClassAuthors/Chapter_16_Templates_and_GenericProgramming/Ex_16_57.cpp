/************************************************************************************************************************************************************
 * @file Ex_16_57.cpp
 * @brief 
 * @date 2024-02-17Exercise 16.57: Compare your variadic version of errorMsg to the error_msg function in § 6.2.6 
 * (p. 220). What are the advantages and disadvantages of each approach?
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * void error_msg(std::initializer_list<std::string> il) :
 *      initializer_list parameter can only be constructed with string type to which all the arguments in the function
 * call should be covertible or same type. Or else the call is in error with stating too many argument.
 *      ex :-
 *              error_msg(42, "hello")  //  error : too many arguments
 *              //  42 cannot be converted as string, "hello" will be converted as string
 *      advantages : if the call has only arguments convertible to string, then this version is best suited, as no template
 *                  deduction, parameter unpacking are neede, so it will be performance effective
 *      dis-advantages : types that are not convertible to string can be used
 *
 * tempate <typename... Args>
 * void errorMsg(std::ostream &os, const Args&... rest); 
 *      advantages : as a variadic template, it can be called with any no and different types.
 *      disadvantages : even if all arguments are of same type or convertible to same type, other than the 1st, the rest
 *                      will form a template parameter pack, and then it will be expanded resulting in to performance 
 *                      overhead. 
 *  
 *************************************************************************************************************************************************************/