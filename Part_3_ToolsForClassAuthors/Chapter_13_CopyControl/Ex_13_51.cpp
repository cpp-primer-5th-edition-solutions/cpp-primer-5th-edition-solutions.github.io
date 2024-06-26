/************************************************************************************************************************************************************
 * @file Ex_13_51.cpp
 * @brief Exercise 13.52: Explain in detail what happens in the assignments of the HasPtr objects on page 541. In particular,
 * describe step by step what happens to values of hp, hp2, and of the rhs parameter in the HasPtr assignment operator.
 * @date 2024-01-27
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * For example, assuming both hp and hp2 are HasPtr objects:
 * hp = hp2; // hp2 is lvalue, so copy_constructor used to copy hp2
 *  1. rhs of '=' will be copied to the parameter of assignment operator using copy_constructor
 *  2. (ie) the parameter rhs will be constructed using copy_constructor
 *  3. contents of lhs and rhs is swaped using swap function, so now lhs will have the contents of rhs and vice-versa
 *  4. assignment returns a reference to lhs
 *  5. as rhs is temporary object it will be destroyed, which calls free on rhs on destruction which destroys the old value of lhs
 *  6. At the end hp and hp2 both will have same value and old value of hp is destroyed
 *      
 * hp = std::move(hp2);  //  rhs is rvalue, move_constructor is used construct parameter of '='
 * 1. inside move constructor resources are moved, (ie) the temp object's ps will be initialized to hp2.ps
 * 2. then it will make hp2.ps = 0, so that hp2 is in valid state, that is valid to destroy and destroying which will not affect
 *    the new object
 * 3. now in assignment operator, contents are swaped, so lhs has the contents of rhs and vice-versa
 * 4. at the end of the block, rhs gets destroyed which calls free() on the oldvalue of lhs
 * 5. at the end, hp will have the value of hp2, and hp2 will be in valid state, which can be assigned a new value or destroyed
 *    but we cannot assume anything about the oldvalue

 *************************************************************************************************************************************************************/

