/************************************************************************************************************************************************************
 * @file pvtunique_ptr.cpp
 * @brief pvtunique_ptr template which imitates the unique_ptr library type
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/
#ifndef PVTUNIQUE_PTR_CPP 
#define PVTUNIQUE_PTR_CPP

#include <iostream>
#include <functional>
#include <exception>

template <typename T> class pvtsmart_ptr;
template <typename T> class pvtshared_ptr;

template <typename T, typename D = std::function<void(void)>>
class pvtunique_ptr : public pvtsmart_ptr<T> {
    friend class pvtshared_ptr<T>;
    typedef D deleter_type;
    public :
        pvtunique_ptr();                                            //  default constructor
        pvtunique_ptr(T *q);                                        //  constructor taking pointer
        pvtunique_ptr(D deleter_);                                  //  constructor taking deleter
        pvtunique_ptr(const pvtunique_ptr &) = delete;              //  cannot be copied    
        pvtunique_ptr(pvtunique_ptr &&);                            //  can be moved  
        pvtunique_ptr & operator=(const pvtunique_ptr &) = delete;  //  cannot be assigned
        pvtunique_ptr & operator=(pvtunique_ptr &&rhs);             //  can be moved 
        ~pvtunique_ptr();                                           //  destructor        
        pvtunique_ptr & operator=(T *p);                            //  takes only a nullptr, makes ptr null    
        T * release();                                              //  returns stored ptr, makes ptr null
        void reset(T *q = nullptr);                                 //  resets the ptr to point q if supplied or nullptr
        const T * get() const = delete;                             //  delets the inherited function        
    private :
        std::function<void (T *)> deleter = nullptr;
        void free();

};

template <typename T, typename D>
pvtunique_ptr<T,D>::pvtunique_ptr() : pvtsmart_ptr<T>() {}

template <typename T, typename D>
pvtunique_ptr<T,D>::pvtunique_ptr(T *q) : pvtsmart_ptr<T>(q) {}

template <typename T, typename D>
pvtunique_ptr<T,D>::pvtunique_ptr(D deleter_) 
    : pvtsmart_ptr<T>(), deleter(deleter_) {}

template <typename T, typename D>
pvtunique_ptr<T,D>::pvtunique_ptr(pvtunique_ptr &&source) 
    : pvtsmart_ptr<T>(std::move(source.ptr)), deleter(std::move(source.deleter)) {
        source.ptr = nullptr;
}

template <typename T, typename D>
pvtunique_ptr<T,D> & pvtunique_ptr<T,D>:: operator=(pvtunique_ptr &&rhs) {
    if(this->ptr == rhs.ptr) {
        return *this;
    }
    free();
    this->ptr = std::move(rhs.ptr);
    this->deleter = std::move(rhs.deleter);
    rhs.ptr = nullptr;
    rhs.deleter = nullptr;
    return *this;
}

template <typename T, typename D>
pvtunique_ptr<T,D>::~pvtunique_ptr() {
    free();  
} 

template <typename T, typename D>
pvtunique_ptr<T,D> & pvtunique_ptr<T,D>::operator=(T *p) {
    if (p == nullptr) {
        free();
        this->ptr = nullptr;
    }    
    else {
        throw std::runtime_error("unique_ptr only supports assigning nullptr");
    }

    return *this;
}

template <typename T, typename D>
void pvtunique_ptr<T,D>::free() {
    deleter ? deleter(this->ptr) : delete this->ptr;
}      
        
template <typename T, typename D>
T * pvtunique_ptr<T,D>::release() {
    T *temp = this->ptr;
    this->ptr = nullptr;
    return temp;
}
      
template <typename T, typename D>
void pvtunique_ptr<T,D>::reset(T *q) {
    free();
    this->ptr = q;
}       
    
#endif