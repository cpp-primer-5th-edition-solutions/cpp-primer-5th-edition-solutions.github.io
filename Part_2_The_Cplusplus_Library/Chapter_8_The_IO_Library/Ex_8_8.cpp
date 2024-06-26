/************************************************************************************************************************************************************
 * @file Ex_8_8.cpp
 * @brief Exercise 8.8: Revise the program from the previous exercise to append its output to its given file. Run the program
 *        on the same output file at least twice to ensure that the data are preserved.
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
 *************************************************************************************************************************************************************/

#include <string>
#include <iostream>
#include <fstream>

struct Sales_data{
    std::string book_no;
    double units_sold;
    double revenue;
};

int main(int argc, char **argv){                    
    std::ifstream ifile(*(argv + 1));       // opens file to read from the first argument 
    if(!ifile){
        std::cerr << "Unable to open file";
        return -1;
    }

    std::ofstream ofile(*(argv + 2));       //  opens file to write given by the second argument, file will be created if already doesn't exist
    if(!ofile){
        std::cerr << "Unable to open file";
        return -1;
    }

    Sales_data total;
    double price;
    if( ifile >> total.book_no >> total.units_sold >> price){         //  condition checks for valid input
        total.revenue = total.units_sold * price;
        Sales_data trans;
        while(ifile >> trans.book_no >> trans.units_sold >> price){  //  transactions are read and processed until eof
            trans.revenue = trans.units_sold * price;
            if( total.book_no == trans.book_no ){
                total.revenue += trans.revenue;
                total.units_sold += trans.units_sold;
            }else{
                ofile << "\n" << total.book_no << " " << total.units_sold << " " << total.revenue ;
                total = trans;
            }
        }
        ofile << "\n" << total.book_no << " " << total.units_sold << " " << total.revenue;
    }else{
        std::cerr << "NO INPUT";
        return -1;
    }

    return 0;
}