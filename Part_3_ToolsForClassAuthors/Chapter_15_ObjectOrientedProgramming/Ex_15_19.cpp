/************************************************************************************************************************************************************
 * @file Ex_15_19.cpp
 * @brief Exercise 15.19: Assume that each of the classes from page 612 and page 613 has a member function of 
 * the form: 
 *      void memfcn(Base &b) { b = *this; }
 * For each class, determine whether this function would be legal.
 * @date 2024-02-04
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * Base class : ok
 * Pub_Derv : ok 
 * Priv_Derv : ok
 * Prot_derv : ok
 * Derived_from_public : ok
 * Derived_from_private : error : base is private as Priv_Derv derives through private derivation
 * Derived_from_protected : ok : base is protected as Prot_Derv derives through protected derivation
 * 
 *************************************************************************************************************************************************************/

 class Base {
 public:
      void pub_mem();      // public member
  protected:
       int prot_mem;       // protected member
  private:
      char priv_mem;       //private member
 };
 
 struct Pub_Derv : public Base {     
      char g() { return prot_mem; }
      void memfcn(Base &b) { b = *this; }
 };
 
 struct Priv_Derv : private Base {       
    int f1() const { return prot_mem; }
    void memfcn(Base &b) { b = *this; }
  };
 
 struct Prot_Derv : protected Base {
    void memfcn(Base &b) { b = *this; }
 };

 struct Derived_from_Public : public Pub_Derv {   
      int use_base() { return prot_mem; }
      void memfcn(Base &b) { b = *this; }
 };
  
 struct Derived_from_Private : public Priv_Derv {     
    void memfcn(Base &b) { b = *this; }   //  error : cannot use Base class objects, as Base is private in Priv_Deriv
 };

struct Derived_from_Protected : public Prot_Derv {
    int use_base() { return prot_mem; }
    void memfcn(Base &b) { b = *this; }
};

