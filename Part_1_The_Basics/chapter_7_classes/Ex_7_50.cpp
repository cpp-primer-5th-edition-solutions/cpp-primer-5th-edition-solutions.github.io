/************************************************************************************************************************************************************
 * @file Ex_7_50.cpp
 * @brief Exercise 7.50: Determine whether any of your Person class constructors should be explicit
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

struct Person;                  
std::istream & read(std::istream &, Person &);

struct Person{
friend std::istream & read(std::istream &is, Person &item);        //   declared as friend so that a user can access non-public member 
friend std::ostream & print(std::ostream &os,const Person &item);  
public :
    Person() = default;                     // default constructor
    explicit Person(std::istream &is) {              // constructor that uses read function to prompt the user 
        read(is, *this);
    }
    Person(const std::string &name_p, const std::string &address_p) :
        name(name_p), address(address_p) {} // constructor that takes a name and a address
private :
    std::string name;
    std::string address;
};

std::istream & read(std::istream &is, Person &item){
    is >> item.name >> item.address;
    return is;
}

std::ostream & print(std::ostream &os,const Person &item){
    os << item.name << item.address;
    return os;
}

int main(){
    Person p1, p2(std::cin), p3("vijai","Poonamallee");
    print(std::cout, p1) << std::endl;
    print(std::cout, p2) << std::endl;
    print(std::cout, p3) << std::endl;

    return 0;
}

/**
 * Person(std::iostream &) is declared as explicit, as there is no point in writing data to a temperory object from a iostream
 * as data will be discarded, there is no use in Person class
*/