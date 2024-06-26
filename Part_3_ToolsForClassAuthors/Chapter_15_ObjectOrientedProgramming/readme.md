
# <p style = "text-align : center; color : grey">OBJECT ORIENTED PROGRAMMING </p>

**object oriented programming**, method of writing program using **inheritance, data-abstraction, and dynamic binding**       

## INHERITANCE 
*Inheritance* is concept of defining a class in-terms of another class, where the class that inherits is called **derived class** and the class from which it inherits is called **base class**. When a class inherits from another class, the interface of the base class becomes the part of the interface of the derived class.       
```c++
        class Foo {
         public :
            void greet() {
                std:cout << "HELLO WORLD" << std::endl;
            }
         };

         class Bar : public Foo {
         public :
            void message() {
                std::cout << "oops" << std::endl;
            }
         };

         base class : Foo
         derived class : Bar

         Since class Bar inherits from the class Foo, Foo's public member becomes the public member of Bar. A derived object can use the base class members directly by their name, we can call base class member on a derived object.
         
         Foo.greet();   //  HELLO WORLD
         Bar.greet();   //  HELLO WORLD
         Bar.message(); //  oops 
```
**class derivation list**, list of clas names from which the derived class inherits specified after a colon(:) preceded by derived class name.      
```c++
    class Bar : public Foo, public Dummy {   
        ..../body
    };
    // class derivation list is what comes after ":", it specifies the names of the base classes and derivation access specifier.
```
**base class**, the class from which another class inherits.
**derived class**, the class which inherits from another class.
**direct base class**, class name specified in the class derivation list.
**in-direct base class**, class from which the class in the derivation list has inherited.     
```c++
    class base {

    };

    class derived : public base {

    };

    class derived_from_derived : public derived {

    };
```

    base : 
        direct base class to the derived class
        in-direct base class to the class derived_from_derived

    derived : 
        derived class of base
        direct base class to the derived_from_derived class

    derived_from_derived :
        derived class of derived which itself is derived from base.

## ACCESS SPECIFIERS 
### member access specifier
**private** members of the base class are not accessible to the derived class, or users of the class. Only a friend has access.         
**public** members of the base class are accessible to the derived object, users of the class and friend.      
**protected** members of the base class are accessible to the derived class and friends of the derived class but not the users of the base class, friend and derived class can access only through a derived object.      
 ```c++
 
        class Base {
            public :
                int pub_mem;
            private :
                int pri_mem;
            protected :
                int pro_mem;
        };
        
        class Derived : public Base{
            public :
                void show() {
                    std::cout << pub_mem   // ok : public member of the base  
                              << pri_mem   // error : private member of the base 
                              << pro_mem   // ok : protected member of the base
                }
        };
 ```

### Derivation access specifier
**private inheritance**, members of the base class whether it is public, protected or private, they all become private members of the derived class.      
**protected inheritance**, public and protected members of the base class becomes protected members of the derived class.      
**public inheritance**, public members (ie) interface of the base class becomes interface (ie) public members of the derived class.
*derivation access specifier* has no effect on whether the members and friends of derived class may access the members of its own direct base class. Access to the base class members is controlled by the access specifiers in the base class itself. derivation access specifier only controls the access to the users, classes that derives from derived class and their friends. 

```c++
class Base {
    public :  //  members, friends, all users - derived class, friends of derived class, general users              
        int pub_mem_base;      
    private :   //  members, friends only
        int pri_mem_base;
    protected : //  members, friends and "derived class can access through its object" 
        int pro_mem_base;
    friend void friend_of_Base(Base &b);
};


/*  when a derived class derives through public derivation from base, every member in base is treated like corresponding member in derived
 *  private of derived = private of derived + private of base
 *  public of derived = public of derived + public of base
 *  protected of derived = protected of derived + protected of base
 */
class Pub_Derv : public Base {
    public :
        int pub_mem_Pub_Derv;
        void access_base(Base &b){
            std::cout << b.pub_mem_base ;  //  ok : only public members can be accessed here, protected members can only be accessed through a derived class object 
            std::cout << pro_mem_base;     //  ok : this->pro_mem_base(accessing through derived class), but we cannot access b.pub_mem_base
        }                                       
    private :
        int pri_mem_Pub_Derv;
    protected :
        int pro_mem_Pub_Derv;
    friend void friend_of_Pub_Derv(Base &b, Pub_Derv &pd);
};

/* private derivation : all members of base resides as the private members of derived, 
 * (ie) when a derived object is constructed it has two parts : base subobject and derived subobject.
 * when derived class derives Base through private derivation, the entire base subobject resides in the private part of the desired subobject 
 * NOTE : Derivation access specifier only dictates the access to members and friends of classes which is derived out of this derived class
 * so the base class is private part of this class, who ever has access to the private member will have access to the base part. */
class Pri_Derv : private Base {
    public :
        int pub_mem_Pri_Derv;
        void access_base(Base &b){
            std::cout << b.pub_mem_base;    //  ok : public mem of base is accessible everyrwhere
            std::cout << pro_mem_base;      //  ok : this->pro_mem_base is accessible to the member of derived
        }
    private :
        int pri_mem_Pri_Derv;
    protected :
        int pro_mem_Pri_Derv;
    friend void friend_of_Pri_Derv(Base &b, Pri_Derv &p);
};

class Pro_Derv : protected Base {
    public :
        int pub_mem_Pro_Derv;
        void access_base(Base &b){
            std::cout << b.pub_mem_base;  // ok
            std::cout << pro_mem_base;    // ok : this->pro_mem_base;  
            //  pri_mem_base is not accessible, therefore a friend of this cannot access it
        }
    private :
        int pri_mem_Pro_Derv;
    protected :
        int pro_mem_Pro_Derv;
    friend void friend_of_Pro_Derv(Base &b, Pro_Derv &p);
};

/* when a class is derived from other, which itself is a derived class derived from another one, then
 * each class control access to its own members.
 * private member : access to its own members and friend is provided
 * protected member : along with above two, derived class and its friends, and all the classes that derives further
 * from the derived class and friends of those classes has access but only through its own object.
 * (ie) for a derived class, it can access through this->pro_base, but not base.pro_base
 * (ie) for a derived_from_derived_class, it can access through this->pro_base, but not base.pro_base and derived.pro_base and not by friend
 * (ie) a protected member is protected by the derived object, so it can be accessed through this.
 */
class Derived_from_Pub_Der : public Pub_Derv {
    public :
        int pub_mem_Derived_Pub_Der;
        void access_bases(Base &b, Pub_Derv &p){
            std::cout << b.pub_mem_base;    // ok : public member can be accessed by everyone
            std::cout << p.pub_mem_Pub_Derv;  // ok : public member can be accessed by everyone
            std::cout << pro_mem_base;  //  ok : this->pro_mem_base can be accessed by this
        //  std::cout << p.pro_mem_base; // error : can be accessed by this or friend of this
        }

    private :
        int pri_mem_Derived_Pub_Der;
    protected :
        int pro_mem_Derived_Pub_Derv;
    friend void friend_of_Derived_from_Pub_Derv(Base &b, Pub_Derv &p, Derived_from_Pub_Der &dpd);
    //  a friend can access the pro_mem of direct base class only if variable name is used in the declaration
    //  (ie)absence of 'dpd' in declaration will give errors if we call pro_mem_Pub_Der.
};

class Derived_from_Pri_Der : public Pri_Derv {
    public :
        int pub_mem_Derived_Pri_Der;
        void access_bases(Pri_Derv &pd){
            // base object cannot be accessed here as it private even base.pub_mem cannot be accessed
            // no access pd.base_subobject as it is private in pd
            // no access to Pri_Der protected members

            std::cout << pro_mem_Pri_Derv;  //  ok : this->pro_mem_Pri_Derv
            std::cout << pub_mem_Pri_Derv;  //  ok : this->pub_mem_Pri_Derv
        }

    private :
        int pri_mem_Derived_Pri_Der;
    protected :
        int pro_mem_Derived_Pri_Derv;
    friend void friend_of_Derived_from_Pri_Der(Pri_Derv &pd, Derived_from_Pri_Der &dpd);
};

class Derived_from_Pro_Der : public Pro_Derv {
    public :
        int pub_mem_Derived_Pro_Der;
        void access_bases(Base &b, Pro_Derv &pd){
            std::cout << b.pub_mem_base;   //  ok : public member
            
            std::cout << pd.pub_mem_Pro_Derv; //  ok : public member

            std::cout << pub_mem_base;       // ok : public member
            std::cout << pro_mem_base;       //  ok : this->pro_mem_base   

            std::cout << pub_mem_Pro_Derv;   //   ok : public
            std::cout << pro_mem_Pro_Derv;   //   ok : this->pro_mem_Pro_Derv;
        }
    private :
        int pri_mem_Derived_Pro_Der;
    protected :
        int pro_mem_Derived_Pro_Derv;

    friend void friend_of_Derived_from_Pro_Derived(Base &b, Pro_Derv &pd, Derived_from_Pro_Der &dpd);
};

void friend_of_Base(Base &b){
    std::cout << b.pub_mem_base;  //   ok : friend to base can access all members of base
    std::cout << b.pro_mem_base;  //   ok : friend to base can access all members of base
    std::cout << b.pri_mem_base;  //   ok : friend to base can access all members of base
}

void friend_of_Pub_Derv(Base &b, Pub_Derv &pd){
    std::cout << b.pub_mem_base ;    // ok : only public member can be accessed here as Pub_Derv is a public derived from base

    std::cout << pd.pro_mem_base;    // ok : protected member can be accessed through derived object  

    std::cout << pd.pri_mem_Pub_Derv;   //  ok : friend of a class has access to all the objects members
    std::cout << pd.pub_mem_Pub_Derv;   //  ok : friend of a class has access to all the objects members
    std::cout << pd.pro_mem_Pub_Derv;   //  ok : friend of a class has access to all the objects members
}                                    


void friend_of_Pri_Derv(Base &b, Pri_Derv &p){
    std::cout << b.pub_mem_base;  // ok : base class has given access of public member of its object to everyone
    std::cout << p.pub_mem_base;  // ok : friend has access to all members of a class including private members
    std::cout << p.pro_mem_base;  // ok : friend can access, but b.pro_mem_base is not accessible.
}

void friend_of_Pro_Derv(Base &b, Pro_Derv &p){
    std::cout << b.pub_mem_base; //  ok : public member is accessible to all
    std::cout << p.pub_mem_base; //  ok : friend has access all members of a class
    std::cout << p.pro_mem_base; //  ok : friend has access to all members of a class   
}

void friend_of_Derived_from_Pub_Derv(Base &b, Pub_Derv &pd, Derived_from_Pub_Der &dpd){
    std::cout << b.pub_mem_base;  // ok : public member can be accessed by every one

    std::cout << pd.pub_mem_base; // ok : public member

    std::cout << dpd.pub_mem_base; // ok : public member, but not dpd.pro_mem_base

    std::cout << dpd.pub_mem_Pub_Derv; // ok : public member
    std::cout << dpd.pro_mem_Pub_Derv; // ok : pro_mem can be accessed by a friend

    std::cout << dpd.pub_mem_Derived_Pub_Der;
    std::cout << dpd.pro_mem_Derived_Pub_Derv;
    std::cout << dpd.pro_mem_Derived_Pub_Derv;
}

void friend_of_Derived_from_Pri_Der(Pri_Derv &pd, Derived_from_Pri_Der &dpd){
    //  base object independent or subobject of direct base class, as the derivation is private, no access to friend
    //  (ie) all members of base are redeclared as private to this and its friends
    std::cout << pd.pub_mem_Pri_Derv;
   
    std::cout << dpd.pub_mem_Pri_Derv;
    std::cout << dpd.pro_mem_Pri_Derv;

    std::cout << dpd.pro_mem_Derived_Pri_Derv;
    std::cout << dpd.pub_mem_Derived_Pri_Der;
    std::cout << dpd.pri_mem_Derived_Pri_Der;
 }

void friend_of_Derived_from_Pro_Derived(Base &b, Pro_Derv &pd, Derived_from_Pro_Der &dpd){
    std::cout << b.pub_mem_base;   //  ok : protected member of direct base class
            
    std::cout << pd.pub_mem_Pro_Derv; //  ok : public member
            
    std::cout << dpd.pub_mem_base;       // ok : public member
    std::cout << dpd.pro_mem_base;       //  ok : this->pro_mem_base   

    std::cout << dpd.pub_mem_Pro_Derv;   //   ok : public
    std::cout << dpd.pro_mem_Pro_Derv;   //   ok : thsi->pro_mem_Pro_Derv;
}   

```

### Virtual Functions 
Base class declares a function to be overriden by the derived class by declaring it as virtual. When other members are inherited, derived class may override the virtual function with a type specific behaviour, if it doesn't override, it will be inherited as it is. Derived class overrides the virtual function by defining a function with same name, same parameter list, const and reference qualifiers.     

### static type
Type with which a variable is declared or expression yields is called static type of the variable, it will known at compile time.

### Dynamic type
Type of the object in memory to which the varible or expression represents is called dynamic type of the variable, it will be known at run-time.
- static type and dynamic type of a varibles are same except when it comes to inheritance.
- static type and dynamic type of a pointer or reference to a base_type can be different
- When derived class object is constructed, it will have two parts, one will be derived part subobject(members of the derived class) and another will be base part subobject(that is members of the base class). As because every derived object has base part in it, we can use a pointer or reference to a base class to point a derived object which is derived from that base class. This is known as derived to base conversion.
**derived to base conversion** accessiblity is controled by base class (ie) if base class is accessible then derived to base conversion is accessible in simple terms if public member of the base class is accessible, then derived to base conversion is possible.       

## Dynamic binding 
- Choosing which function to run at **run-time** is called dynamic binding.
- When a pointer or reference to a base class is used, the object to which is points in memory will be only known at run-time. When a virtual function is called through a base class pointer or reference, compiler generates a code to know which function to call based on the dynamic type of the object.
```c++
class base {
    public :
        virtual void print() const {
            std::cout << "base::print" << std::endl;
        }
};

class derived : public base {
    public :
        void print() const override {
            std::cout << "derived::print" << std::endl;
        }
};

int main() {
    derived d1;
    base b1;

    base *p, &r = d1;  //  derived to base conversion, static type = pointer to base, dynamic type = derived type
    r.print()  //  calls derived::print() 

    p = &b1    //  static type and dynamic type are both same, base type
    p->print() //  calls base::print()

    p = &d1    //  static type is pointer to base, dynamic type is derived type, derived to base conversion
    p->print() //  calls derived::print() 
}
```
**sliced down**, when a derived class object is assigned to an object of base type, then only the base part contained in the derived object will be assigned, we say the derived object is sliced down.

## Abstract base class 
Base class which has one or more pure-virtual function, is called an abstract base class. We cannot create an object of abstract base class, it can only be created as a part of the derived object. If a derived class doesn't override the pure virtual function from base, then it inherits the pure-virtual which makes the derived class too an abstract base class.     
```c++
class abstract_base {
    public :    
        virtual void display() = 0;  //  pure virtual function
        void greet() {
            .../body
        }
};

class derived : public abstract_base {
    public :
        void display() {
            .../ body
        }
};

abstract_base ab1;   //  error : abstract_base class object cannot be created directly
derived d1;          //  ok
d1.display()         //  ok
d1.greet()           //  ok : derived object has the abstract_base subobject in it.   
```
**pure virtual function**, a virtual function which is declared as pure virtual function as writing = 0, after the parameter_list of the function.      

    class Foo {
        public :
            virtual void display(int n) = 0;   // pure virtual function.
    };

## Polymorphism
Writing type independent programs with type specific behaviour through the use of inheritance and dynamic binding is known as Polymorphism(many forms) (ie) calling virtual functions in a type independent manner through a pointer or reference of the base class.
