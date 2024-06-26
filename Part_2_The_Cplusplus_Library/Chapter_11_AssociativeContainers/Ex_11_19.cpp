/************************************************************************************************************************************************************
 * @file Ex_11_19.cpp
 * @brief Exercise 11.19: Define a variable that you initialize by calling begin() on the multiset named bookstore from § 11.2.2
 * (p. 425). Write the variable’s type without using auto or decltype.
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <set>
#include <vector>
#include <string>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

struct Sales_data;   
std::istream & read(std::istream &, Sales_data &); 


struct Sales_data{

friend std::istream & read(std::istream &is, Sales_data &item);     
friend std::ostream & print(std::ostream &os, const Sales_data &item);     
public :                            
    std::string isbn() const {      
        return book_no;
    }

    double avg_price() const;       
    Sales_data & combine(const Sales_data &rhs);

    
    Sales_data() : Sales_data("", 0, 0) {                    
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    Sales_data(std::istream & is) : Sales_data("",0,0) {   
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        read(is, *this);                                   
    }

    
    Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
        std::cout << "Sales_data(const std::string book_no_p) : invoked" << std::endl;
    }

    
    Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) :
            book_no(book_no_p), units_sold(units_sold_p), revenue( units_sold_p * price ) {
                std::cout << "Sales_data(const std::string book_no_p, const unsigned units_sold_p, const double price) : invoked"
                          << std::endl;  
            }
    
private :                                          
    std::string book_no;                           
    unsigned units_sold = 0 ;                      
    double revenue = 0;                            
};

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
    return lhs.isbn() < rhs.isbn();
}

Sales_data & Sales_data::combine(const Sales_data &rhs){  
    units_sold += rhs.units_sold;                         
    revenue += rhs.revenue;

    return *this;                                   
}

std::istream & read(std::istream &is, Sales_data &item){
    std::cout << "Enter the transactin details[isbn count price] : \n";
    double price;
    is >> item.book_no >> item.units_sold >> price;
    item.revenue = item.units_sold * price;
    return is;
}

std::ostream & print(std::ostream &os, const Sales_data &item){
    os << item.book_no << " " << item.units_sold << " " << item.revenue ;
    return os;
}

inline double Sales_data::avg_price() const {
    return revenue / units_sold;
}

int main(){
    std::multiset<Sales_data, bool (*) (const Sales_data &lhs, const Sales_data &rhs) > bookstore(compareIsbn);
    bookstore.insert(Sales_data("45677"));
    bookstore.insert(Sales_data("12345", 6, 9.8));
    std::multiset<Sales_data>::iterator beg = bookstore.begin();
    print(std::cout , *beg);     
}