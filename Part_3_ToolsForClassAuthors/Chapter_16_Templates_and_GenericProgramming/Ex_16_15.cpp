/************************************************************************************************************************************************************
 * @file Ex_16_15.cpp
 * @brief Exercise 16.15: Implement input and output operators for your Screen template. Which, if any, friends
 *  are necessary in class Screen to make the input and output operators work? Explain why each friend declaration, 
 * if any, was needed.
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <string>
//  definition of class template
template <std::string::size_type X, std::string::size_type Y> 
class Screen {
    friend inline std::ostream & operator<<(std::ostream & out, Screen const &sc) {
        out << sc.contents;
        return out;
    }

    friend inline std::istream & operator>>(std::istream &in, Screen &sc) {
        char ch;
        in >> sc.cursor >> ch;
        sc.contents[sc.cursor] = ch;
        return in;
    }
    public : 
        typedef std::string::size_type pos;   // to hide type of contents

        Screen() : height(X), width(Y), contents(std::string(X*Y, '*')) {}     //  default constructor 

        // takes height and width of screen and initilises the contents with ' '
        Screen(const pos h_p, const pos w_p) : height(h_p), width(w_p), contents(std::string(h_p * w_p, '*')) { std::cout << contents.size() << std::endl;}

        // takes height, width, and character to intialises contents
        Screen(const pos h_p, const pos w_p, const char ch) : height(h_p), width(w_p), contents(std::string(h_p * w_p, ch)) { std::cout << contents.size() << std::endl;}

        //  get() returns the character at current cursor position if contents is not empty or else returns -1
        char get() const {
            return (contents.empty()) ? -1 : contents[cursor] ;
        }

        //  get(r,c) returns the character at the position specified by row and coloumn, if position doesn't exist it returns -1
        char get(const pos r, const pos c) const ;

        //  moves the cursor to a position specified by row and coloumn, if position doesn't exist returns character at the end of screen
        Screen move(const pos r, const pos c);

        Screen set(const char ch);    //  writes a character at current cursor position

        Screen set(const pos r, const pos c, char ch);  //  writes a character at specified position

        
        // const member function to call do_display() from const obj, as 'this' is pointer to const, *this is reference to const
        const Screen display(std::ostream &os) const {
            do_display(os);
            return *this;
        }

        // non-const member function to call do_display()
        Screen display(std::ostream &os){
            do_display(os);
            return *this;
        }

        //  it prints the contents of the screen, declared as const for const display() to call 
        void do_display(std::ostream &os) const {
            os << contents;
        }

    private :
        pos height = 0;
        pos width = 0;
        pos cursor = 0;        // cursor is the index of the contents, so starts from zero  
        std::string contents;  // if height = 4, width = 5, then contents will be of size = 4 * 5
};

//  validity of the position is checked based on, height implifies rows, so height >= r or if height is greater than specified coloumn should be lesser than or equal to width
template <std::string::size_type X, std::string::size_type Y> 
inline char Screen<X,Y>::get(const pos r, const pos c) const {
    int row = r * width - 1 ;
    if(contents.empty()){
        return -1;
    }else if( contents.size() <= row + c){
        return contents.back();
    }else{
        return contents[row + c] ;         //  -1 is to account that index starts from zero
    }
}

template <std::string::size_type X, std::string::size_type Y> 
inline Screen<X,Y> Screen<X,Y>::move(const pos r, const pos c) {
    int row = r * width - 1;
    if(!contents.empty()){
        if( contents.size() <= row + c){
            cursor = contents.size() - 1;     
        }else{
            cursor = row + c;
        }
    }    
    return *this;
}

template <std::string::size_type X, std::string::size_type Y> 
inline Screen<X,Y> Screen<X,Y>::set(const char ch){
    if(contents.empty()){
        contents.push_back(ch);    
    }else{
        contents[cursor] = ch;
    }

    return *this;
}

template <std::string::size_type X, std::string::size_type Y> 
inline Screen<X,Y> Screen<X,Y>::set(const pos r, const pos c, char ch){
    int row = r * width - 1;
    if(contents.empty()) {
        contents.push_back(ch);
    }else if(contents.size() <= row + c) {    
        contents[contents.size() -1] = ch;
    }else{
        contents[row + c] = ch;
    }

    return *this;
}


int main() {
    Screen<45,90> s1;
    std::cout << s1;
    std::cout << "Enter the pos and char : " << std::endl;
    std::cin >> s1;

    std::cout << s1;
    return 0;

}

/************************************************************************************************************************************************************
 * as output and input stream operators are non-template non-member functions, they have to be declared friends of Screen
 * and they have to defined inline, or else we have to declare them as templates for one to one friendship to work.
 * 
 *************************************************************************************************************************************************************/