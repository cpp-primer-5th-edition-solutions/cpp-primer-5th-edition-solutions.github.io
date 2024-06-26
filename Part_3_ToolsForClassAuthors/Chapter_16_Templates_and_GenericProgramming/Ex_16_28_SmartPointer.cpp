/************************************************************************************************************************************************************
 * @file Ex_16_28.cpp
 * @brief Exercise 16.28: Write your own versions of shared_ptr and unique_ptr.
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

#include <iostream>
#include <functional>
#include "Ex_16_21_DebugDelete.cpp"

template <typename > class weak_ptr;
template <typename T>
class shared_ptr {
    friend class weak_ptr<T>;
    friend inline bool operator==(const shared_ptr &lhs, const shared_ptr &rhs) {
        return lhs.ptr == rhs.ptr;
    }
    friend inline bool operator!=(const shared_ptr &lhs, const shared_ptr &rhs) {
        return !(lhs.ptr == rhs.ptr);
    }

    public :
        shared_ptr() : ptr(nullptr), count(nullptr), del(nullptr) {}   
        shared_ptr(T *ptr_) : ptr(ptr_), count(new size_t(1)), del(nullptr) {}
        shared_ptr(const shared_ptr &p) : ptr(p.ptr), count(p.count), del(p.del) {
            ++*count;
        }

        shared_ptr operator=(shared_ptr rhs) {
            if ( ptr == rhs.ptr ) {
                return *this;
            } 
            free();
            ptr = rhs.ptr;
            count = ++rhs.count;
            del = rhs.del;
        }  
        shared_ptr operator=(shared_ptr &&rhs) {
            if( ptr == rhs.ptr) {
                return *this;
            }
            free();
            ptr = std::move(rhs.ptr);
            count = std::move(rhs.count);
            del = std::move(rhs.del);
        }

        ~shared_ptr() {
            free();
        }

        void setDeleter(std::function<void (T *)> f) {
            del = f;
        }

        void setDelter(std::function<void (T *)> &&f) {
             del = std::move(f);
        }

        T & operator*() const {
            return *ptr;
        }

        T & operator*() {
            return *ptr;
        }

        T * operator->() {
            return &(this->operator*());   
        }

        size_t use_count() const {
            return *count;
        }

        operator bool() const {
            return ptr;
        }
    private :
        T *ptr;
        size_t *count;
        std::function<void (T *)> del;    //  del is a library function object created to hold a callable object with signature void (*), (ie) takes a pointer to T and returns void.
        void free() {
            if(!ptr) {
                return ;
            }
            if(--*count) {
                std::cout << "destructor called ";
                return ;
            }

            delete count;  //  cannot use DebugDelete operator<T>() as it is instantiated with T deduced as type pointed by ptr, to use DebugDelete we need to use another instantiation
            del ? del(ptr) : delete ptr; 
            
        }
};

template <typename T, typename P = DebugDelete>
class unique_ptr {
    public :
        unique_ptr() : ptr(nullptr) {}
        unique_ptr(T *ptr_) : ptr(ptr_){}
        unique_ptr(T *ptr_, P &del_) : ptr(ptr), del(del_) {}
        unique_ptr(T *ptr_, P &&del_) : ptr(std::move(ptr_)), del(std::move(del_)) {} 
        unique_ptr(const unique_ptr &p) = delete;
        unique_ptr(unique_ptr &&p) : ptr(std::move(p.ptr)), del(std::move(p.del)) {}
        unique_ptr & operator=(const unique_ptr &rhs) = delete;
        unique_ptr & operator=(unique_ptr &&rhs) {
            free();
            ptr = std::move(rhs.ptr);
            del = rhs.del;
            rhs.ptr = nullptr;
            return *this;
        } 

        T & operator*(){
            return *ptr;
        }
        
        const T & operator*() const {
            return *ptr;
        }

        ~unique_ptr() {
            free();
        }
    private :
        T *ptr;
        P del = P();
        void free() {
            del(ptr);
        }
};

