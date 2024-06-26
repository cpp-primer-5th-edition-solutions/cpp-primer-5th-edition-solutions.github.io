/************************************************************************************************************************************************************
 * @file Ex_14_21.cpp
 * @brief Exercise 14.21: Write the Sales_data operators so that + does the actual addition and += calls +. Discuss the 
 * disadvantages of this approach compared to the way these operators were defined in § 14.3 (p. 560) and § 14.4 (p. 564).
 * 
 * @date 2024-01-30
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>

struct Sales_data;   
std::istream & read(std::istream &, Sales_data &); 


class Sales_data{      
public :        
    friend std::ostream & operator<<(std::ostream &os, const Sales_data &source);    
    friend std::istream & operator>>(std::istream &is, Sales_data &source);   
    Sales_data operator+(const Sales_data &rhs);
    Sales_data & operator+=(const Sales_data &rhs);             
    std::string isbn() const {      
        return book_no;
    }

    double avg_price() const;       
    Sales_data & combine(const Sales_data &rhs);

    Sales_data() : Sales_data("", 0, 0) {                   
        std::cout << "Sales_data() : invoked" << std::endl;
    } 

    explicit Sales_data(std::istream & is) : Sales_data("",0,0) {    
        std::cout << "Sales_data(std::istream & is) : invoked" << std::endl;
        read(is, *this);                                   
    }

    explicit Sales_data(const std::string book_no_p) : Sales_data(book_no_p,0,0) {   
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

Sales_data Sales_data::operator+(const Sales_data &rhs){
    Sales_data temp;
    temp.units_sold = this->units_sold + rhs.units_sold;
    temp.revenue = this->revenue + rhs.revenue;
    temp.book_no = this->book_no;
    return temp;
}

Sales_data & Sales_data::operator+=(const Sales_data &rhs){
    *this = *this + rhs;
    return *this;
}             

std::istream & operator>>(std::istream &is, Sales_data &source){
    double price;
    is >> source.book_no >> source.units_sold >> price;
    if (is){     //  checks if read was successfull
        source.revenue = price * source.units_sold;
    } else {
        source = Sales_data();
    }

    return is;
}

std::ostream & operator<<(std::ostream &os, const Sales_data &item){
    os << item.book_no << " " << item.units_sold << " " << item.revenue ;
    return os;
}

Sales_data & Sales_data::combine(const Sales_data &rhs){  
    units_sold += rhs.units_sold;                         
    revenue += rhs.revenue;

    return *this;                                   
}

inline double Sales_data::avg_price() const {
    return revenue / units_sold;
}

int main(){
    Sales_data s1("678-987-34x", 10, 2.5), s2(s1);
    s1 += s2;
    std::cout << s1 << std::endl;

    return 0;
}

/************************************************************************************************************************************************************
 * unnecessarily object was copied twice, when a temp(default constructed) was assigned with memberwise addition of lhs and
 * rhs, the temp already holds what += needs, but it has to be copied to the result as return type of + is non-reference,
 * then once again need to copied to lhs in +=. 
 *      where as if + calls +=, then temp was initialised with lhs and += asigns adding temp and rhs, so we can see only once
 * an obect was initialised, then we just added. So this is performance effective.
 * 
 *************************************************************************************************************************************************************/
