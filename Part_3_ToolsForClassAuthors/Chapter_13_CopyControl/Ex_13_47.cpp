/************************************************************************************************************************************************************
 * @file Ex_13_47.cpp
 * @brief Exercise 13.47: Give the copy constructor and copy-assignment operator in your String class from exercise 13.44 in 
 * § 13.5 (p. 531) a statement that prints a message each time the function is executed.
 * @date 2024-01-27
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
#include <cstring>

class String {
    public :
        String() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
        String(const char *p);
        String(const String &source);
        String & operator=(String rhs);
        char * begin() const;
        char * end() const;
        ~String(){ free(); }
        size_t size();
        void reserve(const size_t sz);
        size_t capacity();
        void push_back(const char &ch);
    private :
        void swap(String &lhs, String &rhs);
        void check_n_alloc();
        void realloc(const size_t sz = 0);
        void free();
        std::pair<char *, char *> alloc_n_copy(const char *b, const char *e);
        char * elements;
        char * first_free;
        char * cap;
        std::allocator<char> alloc;
};

String::String(const char *p){
    std::cout << "String(const char *p) : " << std::endl;
    std::cout << "sizeof(p) " << strlen(p) << std::endl;
    auto data = alloc_n_copy(p, p + strlen(p));
    elements = data.first;
    first_free = cap = data.second;
}

String::String(const String &source){
    std::cout << "String(const String &source) :" << std::endl;
    auto data = alloc_n_copy(source.begin(), source.end());
    elements = data.first;
    first_free = cap = data.second;
}

char * String::begin() const {
    return elements;
}

char * String::end() const {
    return first_free;
}

String & String::operator=(String rhs){
    std::cout << "operator=(String rhs) : " << std::endl;
    swap(*this, rhs);
    return *this;
}

void String::swap(String &lhs, String &rhs){
   using std::swap;
   swap(lhs.elements, rhs.elements);
   swap(lhs.first_free, rhs.first_free);
   swap(lhs.cap, rhs.cap);
}

void String::check_n_alloc(){
    if(first_free == cap){
        realloc();
    }
}

size_t String::size(){
    return first_free - elements;
}

void String::reserve(const size_t sz){
    realloc(sz);
}

size_t String::capacity(){
    return cap - elements;
}

void String::realloc(const size_t sz){
    size_t new_capacity;
    if(!sz){
        new_capacity = size() ? 2 * size() : 1;
    }else if( sz && sz > capacity()){
        new_capacity = sz;
    }else {
        return ;
    }

    auto new_elements = alloc.allocate(new_capacity);
    auto new_first_free = std::uninitialized_copy(elements, first_free, new_elements);
    free();
    elements = new_elements;
    first_free = new_first_free;
    cap = elements + new_capacity;
}

void String::free(){
    while(first_free != elements){
        std::destroy_at(--first_free);
    }
    alloc.deallocate(elements, cap - elements);
    elements = first_free = cap = nullptr;
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e){
    auto new_elements = alloc.allocate(e - b);
    auto new_first_free = std::uninitialized_copy(b, e, new_elements);
    return {new_elements, new_first_free};
}

void String::push_back(const char &ch){
    check_n_alloc();
    std::construct_at(first_free++, ch);
}

void print(const String &str){
    for(auto iter = str.begin(); iter != str.end(); ++iter){
        std::cout << *iter ;
    }
    std::cout << std::endl;
}

int main(){
    String str1("hello world"), str2(str1), str3;
    str3 = str1;
    print(str1);
    print(str2);
    print(str3);
    str1.push_back('#');
    str2.push_back('$');
    str3.push_back('&');
    for(auto i = 1; i <= 20; ++i){
        std::cout << str1.size() << " " << str1.capacity() << " " << i + 60 << std::endl;
        str1.push_back(i+60);
    }

    print(str1);
    print(str2);
    print(str3);

    return 0;
}