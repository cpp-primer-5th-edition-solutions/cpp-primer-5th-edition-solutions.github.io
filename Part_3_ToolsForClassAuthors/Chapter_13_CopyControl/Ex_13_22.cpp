/************************************************************************************************************************************************************
 * @file Ex_13_22.cpp
 * @brief Exercise 13.22: Assume that we want HasPtr to behave like a value. That is, each object should have its own copy of
 * the string to which the objects point. We’ll show the definitions of the copy-control members in the next section. However,
 * you already know everything you need to know to implement these members. Write the HasPtr copy constructor and 
 * copy-assignment operator before reading on.
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <memory>

//  class defined to behave like value, (ie) object's state is independent from the other
class HasPtr {
public:
    // constructor that takes a string with empty string as a default value to behave as default constructor
    HasPtr(const std::string& s = std::string())
        : ps(new std::string(s)), i(0){}

    // copy constructor    
    HasPtr(const HasPtr& hp) : ps(new std::string(*(hp.ps))), i(hp.i) {
        std::cout << "copy constructor called" << std::endl;
    } 

    // copy-assignment operator
    HasPtr & operator=(const HasPtr &source){
        *ps = *(source.ps);         
        i = source.i;

        return *this;
    }

    // destructor 
    ~HasPtr(){
        delete ps;
        std::cout << "destructor is run and the memory allocated to hold the string is deleted" << std::endl;
    }

    void info(){
        std::cout << ps << " " << *ps << " " << i << std::endl;
    }
private :
    std::string* ps;
    int i;
};


int main(){
    HasPtr hp1("hello"), hp2(hp1);
    HasPtr hp3("world");
    hp1.info();
    hp2.info();
    hp3.info();
    hp1 = hp3;
    hp1.info();

    return 0;
}

