# <p style = "text-align : center"> COPY CONTROL </p>

* copy constructor
* copy-assignment operator
* move constructor
* move-assignment operator
* destructor
    - all the above constructors are collectively called as copy control. Classes controls what happens when the objects of its type are copied from same type, moved and destroyed.       
** To understand when copy constructors are used, have to understand difference between direct and copy intialisation **
## Direct initialisation vs copy initialisation
When ***objects*** of the class type is constructed, any one of the two kinds of initialisation used normaly.       
**direct initialisation         
copy initialisation**    

      ex:-  string str(str2)            //  direct initialisation
              string str = str2           //  copy initialisation  
              string str("hhhhh")         //  direct initialisation
              string str = "hhhhh"        //  copy initialisation  
              string str(5,'h')           //  direct initialisation  
              string str = string(5,'h')  //  copy intialisation
        as we can see above, copy initialisation happens whenever we initialise an object using '=' operator.
So, what's the difference between the two,     
*direct initialisation* :    
    when we use *direct initialisation* normal function matching happens among the constructors, best match is used to construct the obect.       
*copy initialisation*  :            
    when we use '=' operator to construct an object, copy initialisation happens. Copy initialisation copies the value in to the object being constructed, to do that compiler constructs a temporary object, if the copied object is not of same type it looks for all the ways to convert and then copies the object.              
          
    ex 1 :- 
        class foo{
            public :
                foo(foo){}
                foo(int){}
        };

        case 1:  foo f1(i);   // direct initialisation
                 
                 normal function matching happens among constructors
                 candidate funtions : foo(foo), foo(int)
                 viable funtions    : foo(i)
                 best match         : foo(i)

        case 2: foo f1 = i;   // copy initialisation
                now function matching don't happen.
                since i is not foo type, all ways to convert i to foo type will be considered,
                foo(int) is only avalable way to convert, so it will be used to convert i to temp foo object
                then, temp object will be copied in to new object using foo(foo) constructor
                but, if we mark the constructor as explicit, then there won't be no way to convert so copy initialisation is in error.

        clss foo{
            public :
                explicit foo(foo){}
                explicit foo(int){}
        };

            foo f1(i)   // ok : direct initialisation, through function matching foo(int) is chosen
            foo f1 = i  // error : to copy initisalise there is no way to convert i to foo, as foo(int) is marked as explicit so it can be used only for direct initialisation
            foo f1 = foo(f1) // error, as foo(foo) is marked as explicit to be used by only direct initialisation 


    ex 2 :- 
        class foo{
            public :
                foo(double) {}
                foo(foo) {}
                foo(int) {}
        };

        assume two other non member methods are avaible to convert from int to foo

       foo f1(10)   //  direct initialisation, foo(int) is chosen as the best match among the constructors
       foo f1 = 10  //  copy initialisation, as int is a diff type, all ways to convert int to foo type is considered
                        two constructors exists and two non-member methods are considered, which ever is closer is used to construct temp foo object and then foo(foo) is used to copy the object
       foo f2(f1)   //  direct initialisation, foo(foo) is chosen as the best match among the constructors
       foo f2 = f1  //  copy initilisation, foo(foo) is used to build temp object and copy in to the new object
- copy initialisation is used in the following places
    * '=' operator is used 
    * argument to non-ref parameter type, call by value 
    * non-ref return type, when the value of return is used to initialise the result of the call expression
    * brace initialise the elements in an array or other members of an aggregate class.
    * some containers use copy initialisation to initialise their elements, like  push_back(), insert, list initialisation but emplace() uses direct initialisation
- ordinarily copy constructors are used in copy initialisation.

## COPY CONSTRUCTOR
*COPY CONSTRUCTOR*, is a constructor that takes a reference to a object of its own type and default values for all other parameters.    
>    foo(const foo&)  // copy constructor     

    it is normaly const reference though we can use non-const reference.       
    ordinarily, synthesised copy constructor does a memberwise copy, if class contains an object of array type, then all the elements of the array is copied.        
    if the argument is not reference type, then when copy initialisation happens, to call the copy constructor, we need to use the copy constructor to copy the argument, but to copy the argument again we need to use the copy constructor, this goes on indifinitely.     

Though the compiler is permited to skip the copy/move constructor during copy initialisation to create object directly without a temp object, copy/move constructor should exists and accessible(shouldn't be private), or else it won't work

    class foo{
        public :
            foo(const foo &){}
            foo(int) {}
    };

        foo f1(10)  //  direct initialisation
        foo f1 = 10 // copy initialisation, can be rewriten as foo f1(10) to use foo(int) without calling copy constructor, but copy constructor should be accessible.
        its compiler's choice, it can also use foo(int) to create a temp object and call copy constructor foo(const foo &) to copy the value of the object to the new object

---------------------------------------------------------------------------------------------------------------------------

## copy_assignment operator :  
> T & operator=(const T &)      

copy_assignment operator is a overloaded =,assignment operator. It is defined like any other function, name should be  operator_symbol preceded by keyword operator, a parameter of the same type and returns a lvalue referenceto the object on which it is called.       
It copies the rhs in to the lhs, synthesised one's does a member wise copy.
    t1 = t2;   calls the copy_assignment operator defined for the t1 type on t1. t2 is passed as the argument.

# MOVE    
when copying an temporary object, rather than copying the contents, if we can move the resourses it will be highly performance effective (ie) the resources will be moved from the moved from object to the moved to object. the new object holds the responsibility of the resources and the original will be left in a valid state that can be used to hold a new value or can be destroyed.          
Moving is highly effective when we want to copy data from a object which is about to be destroyed       
literals, temp objects created during a expression, non-reference return type of a function, arithmatic operators, post increment and post decrement operators yield rvalues, rather than copying resources from them, if we can move them gives performance boost.        
Consider a class which allocates memory,     
- copying allocates new space and copies all the data
- moving just copies the pointers of the moved from object, it doesn't allocate any memory and leaves a moved from object in a valid state, (ie) when the moved from object is destroyed it won't do any harm to the new object and its resources     

## rvalue references :
> References are of two types      
**lvalue reference**, reference bound to a lvalue, lvalue are the identity of the object, where as rvalue is the value of the object. A **non const lvalue reference** can only be binded with lvalues.      
 variables, pre increment & decrement , dereferencing operator yields lvalues.        

    ex :-
        Foo f1;
        Foo &r1 = f1;    
    & is used as the type modifier to indicate r1 is lvalue reference type
**rvalue reference**, reference bound to a rvalue, literals, non-reference return type, arithmatic, post increment & decrement are all rvalues, either rvalue reference or const lvalue reference can be bound.       
As we can see, rvalues represents objects that are about to be destroyed, when we create a rvalue reference is bounded to it, an object with persistent state is created, the contents are moved to it and the rvalue reference is binded to it    
Like lvalue references, rvalue references are another names to the objects, but they themselves are not objects.      
So no array of references for neither lvalue nor rvalue can be created. But since an object with persistent state is created, we can get a pointer to the object rvalue reference is bound        

    ex :-
        Foo &&r1 = Foo();
    && is used as the type modifier to indicate r1 is rvalue reference type
#### lvalues persists and rvalues are ephimerals      
    lvalues are objects with persistant state where as rvalues are objects about to be destroyed      
AS we can see, rvalue references are bounded to only objects that are about to be destroyed we cannot bind one to a variable, as a variable is an expression with no operator and single operand and returns a lvalue reference to the variable.     

    ex:- 
        Foo v1;
        Foo &r1 = v1   //  ok : v1 is a lvalue and r1 is a lvalue reference type
        Foo &r2 = 45   //  illegal : 45 is a literal, cannot be binded to a non-const lvalue reference type

        Foo v1;
        Foo &&r1 = v1  //  illegal : v1 is a lvalue, cannot be binded to r1 which is rvalue reference type
        Foo &&r1 = 45  //  ok : r1 is rvalue reference type, so can be bound to a literal that can be converted to Foo

But if we want to bind an rvalue reference to a variable, std::move() need to be used to indicate that we want to move the value    

    ex:-      
        Foo v1;
        Foo &r1 = v1;
        Foo &&r2 = std::move(v1);
As rvalue references steals the resources, by using std::move(), we are promising that v1 won't be used anymore. Though v1 will be in a valid state, no assumptions shall be made about the value it contains.      

    ex:-      
        Foo &&r3 = r2   //  illegal : though r2 is rvalue reference, we cannot bind r3 to it, as rvalue references steal the resources, they own it. And r2 is another name to the varaiable, an expression with only a variable name yields an lvalue, so it cannot be normally binded with another rvalue reference.
        But if we want, we can indicate that we want't to move the resource by using std::move() defined in utility header
        Foo &&r3 = std::move(r2)  //  ok : resources will be moved to r3, r2 will be in a valid state to be destroyed it shouldn't be used any where.         
## move_constructor :     
> T(T &&)          
Move constructors are defined with the class name and takes a parameter of **rvalue reference** of the class type and all other parameters with default values. It will be used to construct objects from rvalue . It moves the resources from the source and leaves the source in a valid state.      
                
    class Foo{      
        Foo(const Foo &)  //  copy constructor
        Foo(Foo &&)       //  move constructor
    };

As move constructors change the state of the moved from object, they take a non-const reference to rvalues where as copy_constructors don't change the source they take a const reference to lvalues.        

## move-assignment operators :
> T& operator=(T &&);      
- return_type : lvalue reference to the object on which the operator is called       
- parameter_type : rvalue reference to the rvalue of the object type      
moves the resources of the the rhs to the lhs and leaves the rhs in a valid state.          
Normaly, copy-assignment takes a const lvalue reference to the rhs as it doen't modify the rhs but since move-assignment modifies the rhs, it takes a rvalue reference to the rhs.           

## std::move(t1)     
Defined in the utility header, returns the rvalue of the t1, it indicates we want to move the resources rather than copy, so it makes move constructor to be invoked to construct the object rather than copy_construct.         
    all built-in types, string supports move operations         

## move_iterators     
dereferencing a iterator yields a lvalue, but when we want to move the resource, we can use *move_iterator* adaptor which when dereferencing yields the rvalue.        
***std::make_move_iterator(iter)*** function takes a iterator and returns the move_iterator to be used with algorithms to reallocate contents         

> move constructors are not implicitly defined when other copy control members are defined.     
> defined as deleted , when compiler cannot synthesise one, when we ask to synthesise using default.     
> noexcept should be mentioned after the parameter list, as the move operations don't allocate any resource, they don't normally throw any exceptions. Containers like vector guarante's that container will be in valid state when any exception occurs during copying, moving, assigning. Unless a move operation mentions noexcept, vector will use copy_constructor.     

    ex:-      
        Foo(Foo &&) noexcept {}     
    
## reference qualifiers      
member operations can be called on both lvalue and rvalue.     

    ex:-    str1 + str2 = str3;     //  Assigns the str3 to the result of adding str1 and str2 which is a rvalue       
To avoid this, member operations can be reference qualified to indicate, on which type it can be called        

    ex:-    struct Foo{    
                Foo & operator=(const Foo &)  & {}   // only be called on a lvalue     
                Foo & operator=(Foo &&)  && {}  // only be called on a rvalue     
            }     

## Destructors 
**Destructors** are special member functions which will be called when an object is destroyed. Destructors is defined to free any memory allocated by the class. Once the body of the *destructor* is finished executing then all the members of the object is destroyed in reverse to the order of declaration implicitly. No return type as they don't return anything and don't take any parameters, they can only be called implicitly when an object is destroyed.
It has the same class name preceded by ~
 ```c++
        class Foo {
            public :
            ~Foo() {
                .../body
            }
        }

 ```

***Any copy control members*** can be declared **default** to get a **synthesised version** and declared **delete** to make the member unavailable or deleted.
```c++
        class Foo {
            public :
                Foo() = default;
                Foo(const Foo &) = default;
                Foo(Foo &&) = default;
                Foo & operator=(const Foo &) = delete;
                Foo & operator=(Foo &&) = delete; 
        }
    /* default constructor, copy constructor and move constructor are declared as default to be synthesised by the compiler
    copy and move assignment operator is declared as delete to make them deleted */      
    
```    

## SWAP
classes that manages resources on their own often defines a *swap()* non-member function, as the algorithms that *rearranges* containers uses swap() to swap the elements.
Library version of swap() works normally by copy and two assignments which unnecessarily allocates memory and use copy constructors to swap, but it can be avoided by just swaping the pointers.
```c++
    // how library swap may work
    void swap(T lhs, T rhs) {
        T temp = lhs;   // copy constructor is used
        lhs = rhs;      // copy-assignment operator is used
        rhs = lhs;      // copy-assignment operator is used
    }

    // is suppose T has pointers to allocated memory, temp will allocate new memory and contents will be copied twice
    //  1. temp = lhs
    //  2. rhs = temp;

    // As we can see it is unnecessary as we can simply copy pointers.

    //  type specific definition of swap
    //  ret_type is void, and takes parameter of reference to class types, defined as non-member and should be declared as friend to access private members.

    void swap(T &lhs, T &rhs) {
        using std::swap;   // using declaration is must as to use library swap for library types
        swap(lhs.ptr, rhs.ptr);  
        swap(lhs.mem, rhs.mem);
    }

    //  should call swap not std::swap, as if any member as its own swap() defined, this will call the type specific
    //  version or else if we used std::swap, it will use library version not the version defined by the type.
As swap() don't allocate memory, it is exception safe by default. 
```



