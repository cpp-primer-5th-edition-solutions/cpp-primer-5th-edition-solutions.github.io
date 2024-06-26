/************************************************************************************************************************************************************
 * @file pvtshared_ptr.cpp
 * @brief pvtshared_ptr template that imitates shared_ptr library type
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#ifndef PVTSHARED_PTR_CPP
#define PVTSHARED_PTR_CPP

#include <iostream>
#include <functional>

template <typename T> class pvtsmart_ptr;                   //  forward declaration
template <typename T> class pvtshared_ptr;                  //  forward declaration
template <typename T, typename D> class pvtunique_ptr;     

template <typename T>       //  swap template declaration
void swap(pvtshared_ptr<T> &lhs, pvtshared_ptr<T> &rhs);

template <typename T>
class pvtshared_ptr : public pvtsmart_ptr<T> {
    friend void swap<T>(pvtshared_ptr<T> &lhs, pvtshared_ptr<T> &rhs);   //  non-member swap, swaps the pointer
    public :
        pvtshared_ptr();                                        //   default constructor.
        pvtshared_ptr(T *, std::function<void (T *)> deleter_ = nullptr); //   constructor that takes a pointer 
        pvtshared_ptr(const pvtshared_ptr &source, std::function<void (T *)> deleter_ = nullptr);  //   copy constructor
        pvtshared_ptr(pvtshared_ptr &&source);                  //   move constructor
        pvtshared_ptr & operator=(const pvtshared_ptr &rhs);    //   copy assignment operator
        pvtshared_ptr & operator=(pvtshared_ptr &&rhs);         //   move assignment operator
        ~pvtshared_ptr();                                       //   destructor
        pvtshared_ptr(pvtsmart_ptr<T> &b);                      //   constructor that takes a unique ptr;

        void swap(pvtshared_ptr & rhs);                         //   swaps the pointers

        bool unique();                                          //   true, if this alone points to the obj
        size_t use_count() const;                               //   returns no.of pointers pointing same object   
        void reset(T *q = nullptr, std::function<void (T *)> deleter_ = nullptr);   //   sets pointer to null, if unique() frees the obj

    private :
        void free(); 
        size_t *count;
        std::function<void (T *)> deleter = nullptr;
};

template <typename T>
pvtshared_ptr<T>::pvtshared_ptr() : pvtsmart_ptr<T>(), count(nullptr) {}

template <typename T>
pvtshared_ptr<T>::pvtshared_ptr(T *ptr_, std::function<void (T *)> deleter_) 
    : pvtsmart_ptr<T>(ptr_), count(new size_t(1)), deleter(deleter_) 
    {}

template <typename T>
pvtshared_ptr<T>::pvtshared_ptr(const pvtshared_ptr &source, std::function<void (T *)> deleter_) 
    : pvtsmart_ptr<T>(source.ptr), count(source.count), deleter(source.deleter) {
    std::cout << "pvtshared_ptr(const pvtshared_ptr &source, std::function<void (T *)> deleter_)" << std::endl;;
    if (deleter_) {
        deleter = deleter_;     
    } 
    ++*count;
}

template <typename T>
pvtshared_ptr<T>::pvtshared_ptr(pvtshared_ptr &&source)
    : pvtsmart_ptr<T>(std::move(source.ptr)), count(std::move(source.count)), deleter(std::move(source.deleter)) {
    std::cout << "pvtshared_ptr(pvtshared_ptr &&source) ";
    source.ptr = nullptr;
    source.count = nullptr;
}

template <typename T>
pvtshared_ptr<T>::pvtshared_ptr(pvtsmart_ptr<T> &b)  
    : pvtsmart_ptr<T>(std::move(b)), count(new size_t(1)) {
      b.ptr = nullptr;
}

template <typename T>
pvtshared_ptr<T> & pvtshared_ptr<T>::operator=(const pvtshared_ptr &rhs) {
    if(this->ptr == rhs.ptr) {
        return *this;
    }

    free();
    this->ptr = rhs.ptr;
    count = rhs.count;
    deleter = rhs.deleter;
    ++*count;

    return *this;
}

template <typename T>
pvtshared_ptr<T> & pvtshared_ptr<T>::operator=(pvtshared_ptr &&rhs) {
    if(this->ptr == rhs.ptr) {
        return *this;
    }

    free();
    this->ptr = std::move(rhs.ptr);
    count = std::move(rhs.count);
    deleter = std::move(rhs.deleter);
    rhs.ptr = nullptr;
    rhs.count = nullptr;
    return *this;
}

template <typename T>
pvtshared_ptr<T>::~pvtshared_ptr() {
    free();
}

template <typename T>
void pvtshared_ptr<T>::free() {
    if(count && --*count) {
        return;
    }

    delete count;
    deleter ? deleter(this->ptr) : delete this->ptr;
} 

template <typename T>
void pvtshared_ptr<T>::swap(pvtshared_ptr &rhs) {
    using std::swap;
    swap(this->ptr, rhs.ptr);
    swap(count, rhs.count);
    swap(deleter, rhs.deleter);
}

template <typename T>
size_t pvtshared_ptr<T>::use_count() const {
    return count ? *count : 0;
}

template <typename T>
inline void swap(pvtshared_ptr<T> &lhs, pvtshared_ptr<T> &rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.count, rhs.count);
    swap(lhs.deleter, rhs.deleter);
}

template <typename T>
bool pvtshared_ptr<T>::unique() {
    return *count == 1 ? true : false;
}

template <typename T>
void pvtshared_ptr<T>::reset(T *q, std::function<void (T *)> deleter_ ) {

    if(--*count == 0) {
        deleter_ ? deleter_(this->ptr) : delete this->ptr;
        delete count;
    }

    if(q) {
        this->ptr = q;
        this->count = new size_t(1);
    } else {
        this->ptr = nullptr;
        count = nullptr;    
    }    
}

#endif
