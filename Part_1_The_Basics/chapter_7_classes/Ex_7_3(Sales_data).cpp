/*  Exercise 7.3: Revise your transaction-processing program from § 7.1.1 (p. 256) to use these members.*/

#include <iostream>

struct Sales_data{
    std::string isbn() const {          //   declared as const member function so that we can call isbn() for const objects
        return book_no;
    }
    
    Sales_data & combine(const Sales_data &rhs);

    std::string book_no;                           //   isbn no                     
    unsigned units_sold;                           //   total no of units sold
    double revenue;                                //   revenue from the total sale of this book
};

Sales_data & Sales_data::combine(const Sales_data &rhs){  //   returns reference of the object for which combine was called, it-
    units_sold += rhs.units_sold;                         //   -mimics the += operator's return value   
    revenue += rhs.revenue;

    return *this;                                   //  this is pointer which is rvalue, to get lvalue we dereference it
}

int main(){
    Sales_data total;
    std::cout << "Enter the list of transactions : \n";
    double price;
    if(std::cin >> total.book_no >> total.units_sold >> price){
        total.revenue = price * total.units_sold;
        Sales_data trans;
        while(std::cin >> trans.book_no >> trans.units_sold >> price){
            trans.revenue = price * trans.units_sold;
            if( total.isbn() == trans.isbn()){      //  isbn() function returns book_no from the corresponding objext
                total.combine(trans);               //  combine() takes trans and returns a reference to total object
            }else{
                std::cout << "\n\t# " << total.book_no << " " << total.units_sold << " " << total.revenue;
                total = trans;
            }
        }
        std::cout << "\n\t# " << total.book_no << " " << total.units_sold << " " << total.revenue;
    }else{
        std::cerr << "NO VALID INPUT" << std::endl; 
    }    

    return 0;
}