/************************************************************************************************************************************************************
 * @file Ex_13_45.cpp
 * @brief Exercise 13.45: Distinguish between an rvalue reference and an lvalue reference.
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * lvalue reference, is a reference bound to a lvalue, (ie) an object with persistant state, expressions that is a reference 
 *      returned from a funtion, assignment, preincrement and predecrement, subcript are examples of expressions that return
 *      lvalue.
 * rvalue reference, is a reference bound to a rvalue, which is a an object with ephimeral state (ie) about to be destroyed,
 *      temporary variable created during evaluating an expression, expressions that return rvalues, literals, returning a non-reference from a function, post
 *      increment and post decrement, arithmatic, relational, bitwise are expression that return rvalues.
 *      rvalue reference steals the state of the object (ie) resources of the object, so it can only bound to a obect to be 
 *      destroyed. This is mainly useful when rather copying an object, moving its resources(pointers) is performance effecient.
 * 
 * ex:-
 *      int i;        //  an lvalue   
 *      int &r1 = i,  //  r1 is an lvalue reference so it can be bound to an lvalue i
 *      int &r2 = 42  //  error : 42 is an rvalue (ie) a literal which is about to be destroyed, so r2, a lvalue ref cannot be bound
 *      int &&rr1 = i //  error : rr1 is an rvalue reference, but i is a lvalue, so rr1 cannot steal the resource which i owns  
 *      int &&rr2 = 42 // 42 is rvalue, a literal about to be destroyed, so it can be bound to an rvalue reference
 *      
 *      int &&rr2 = rr1  // illegal : like any expressions a variable is expression with one operand and no operator, yields
 *                          lvalue. so though rr1 and rr2 are both rvalue references rr2 cannot be bound to rr1. 
 *                          rvalue references steals the resource (ie) there will be only one owner to the value, since rr1
 *                          owns the value it's bounded, we cannot make another rvalue reference to share it.
 *      int &&rr2 = std::move(rr1)  //  std::move(), moves the resources owned by rr1 to rr2, after moving rr1 should not be
 *                          used except assign to it or destroy it. No assumptions shall be made about the value of the moved
 *                          from object (ie) we shouldn't use value of the moved from object.
 *                          
 *************************************************************************************************************************************************************/