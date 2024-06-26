/************************************************************************************************************************************************************
 * @file Ex_15_7.cpp
 * @brief Exercise 15.7: Define a class that implements a limited discount strategy, which applies a discount to
 * books purchased up to a given limit. If the number of copies exceeds that limit, the normal price applies to
 * those purchased beyond the limit.
 * @date 2024-02-03
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include "Ex_15_5_BulkQuote.cpp"

// derived class, derives from Quote
class LimitedQuote : public Quote {     //  interface of Quote is part of the interface of LimitedQuote
public :    
    LimitedQuote() = default;   
    
    LimitedQuote(const std::string &book_no_, double price_, double disc_, size_t max_qty_) 
        : Quote(book_no_, price_), disc(disc_), max_qty(max_qty_) {}

    double net_price(size_t count) const override {
        if(count <= max_qty){
            return count * (1 - disc) * price;
        } else {
            return max_qty * (1 - disc) * price + (count - max_qty) * price;
        }
    }
private :
    double disc;
    size_t max_qty;
};

int main(){
    Quote q1("c++ primer", 89);
    Bulk_quote bq1("discrete maths", 89, 0.2, 100);
    LimitedQuote lq1("mastering c", 65, 0.4, 50);

    print_total(q1, 100);
    print_total(bq1, 99);
    print_total(bq1, 100);
    print_total(lq1, 50);
    print_total(lq1, 52);

    return 0;
}
