# CLASSES     
## Abstraction and Encapsulation     
**Abstraction** is the process of defining the **interface** and **implementation** seperately      
*interface* of the class consists of the operations that users of that class can use to interact with the object      
*implementation* consists of data members, definitions of member functions and any functions needed to define the class that are not for general use     
**Encapsulation** enforses the *seperation* of interface and implementation. A class that is encapsulated *hides* its implementation, users of that class has no access to the implementation, only have access to interface     

A class that uses data abstraction and encapsulation defines an abstract class.    
In an abstract class, class designers worries about the implementation      
and the progammers who use the class does not need to know how the type works, instead they can think ***abstractly*** about
how to use the class    

### class definition
    struct name{
        data members;
        member functions;
    };

    or

    class name{
        data members;
        member functions;
    };

### this pointer 
    when a member function of a class on behalf of an object is called, they are given an extra implicitly defined parameter 
    'this', when we call a mem-function, compiler passes the object's address to this, 
    so, the member functions can access the data members of object on which it is called implicitly using this pointer
    'this' - type
        class_name *const, 
    this is a const pointer to non-const object, as the address of the object should not be changed.
### ***return_type mem_function( parameter_list) const {};***
    To call member functions of a const object, we have to change the type of 'this' is pointer to const, as normal const pointer to non-const object cannot be initialised with const object, Since the 'this' is implicitly defined, to mention 'this' is const 'pointer to const' object we have to use 'const' keyword after the parameter list of the function.
    So that the function can be called on the const object, and these functions are called const member functions

### member definitions outside the class
    member name should be preceded by the class name, the scope operator is used to mention the name_space where member name can be found
    return_type class_name::member_function( parameter_list) {}
    it tells member_function of class_name which takes parameter_list and returns return_type.
    member functions defined inside the class are implicitly inline to the class
    members defined outside the class are not inline by default, if we want them to be inline, we need to define using inline keyword. 

### *this
    to return a reference of the object on which the mem-function is called, we can use 'this' pointer, 
    'this' is a pointer, so it is rvalue, but the references are lvalue, so we dereference 'this' to get the object 

### Constructor
**constructors** are defined by the class to define how its objects can be initialised          
defined inside the class are *inline* by default         
constructors are the mem-functions with class name as their name, they don't have a return type, as they don't return anything       

    default constructor :      
        a constructor which doesn't take any parameters are called default constructor,      
        It uses in-class initialisers if present to initialise the members otherwise they will be default initialised      
    Synthesised default constructor :     
        If the class doesn't define any constructor then compiler implicitly creates a default constructor, which is called synthesised default constructor      
        It will be not synthesised if we declare any other constructor, simply if a class defines a special constructor it surely needs to define its default constructor      
        If we want a default constructor to have the behaviour of synthesised one, it need to declared as default
        class_name() = default;      
    no synthesided default constructor :
        if class has other constructor defined 
        if class has a member which is an object of a class which doesn't have a default constructor    
        if class have built-in type which when default initialised has undefined valued, either these types should be in-class initialised or we need to define our own default constructor

    no const constructor :      
        a constructor may not be declared as const, as it writes to object      
        when a const obect is created, its constness is not assumed untill it is initialised, that is untill the constructor 
        completes the object initialisation, thus constructors can write to the const object during their construction      
    
### Default constructor :
    Default constructor is implicitly(automatically) used whenever an object is 
        1. default initialised 
        2. value initialised
    1. default initialisation happens
        a. non-static variables definitions
        b. arrays at block scope without initialisers
        c. class has another class as a member which has a synthesised default constructor
        d. members of class are not explicitly initialised in a constructor inititalizer list
    2. value initialisation happens
        a. static variable definitions with out initialiser
        b. array initialisation with few initialisers than the size of the array
        c. T(), explicit call for value initialisation like std::string(), std::vector<T> tvec(10) - 10 elements of type 
           T will be value intialised
        d. for value initialisation to work, there should be constructor which takes the value_type as its parameter or else it won't work.    
### constructor initialiser
    int num = 10;  -- initialisation of num, num is alloted memory, and value 10 is writen at the same moment
    int foo;       -- declaration of foo, foo is alloted memory, and default initialised
    foo = 10;      -- value 10 is writen as a second step
    we can see that initialisation is effective than declaration and defining a variable;
    1. Constructor initialisers initialises the members when members are created, and form is
        struct bar{
            bar(T val1, P val2) : member1(val1), member2(val2) {}
            T member1;
            P member2;
        };
    members are initialised by the initialisers before execution reaches the constructor body
    So if we don't provide initialiser, members are default initialised before constructor body is executed, so to initialise the members we have to use constructor initialisers rather than assigning values in constructor body, as the members would have been already initialised
    2. More than the efficiency, 
            a. members of const objects, 
            b. const members
    cannot be assigned, they can only be initialised, in the absence of initilisers, const objects will have undefined value

### Delegating Constructors
    Constructors can delegate its work to other constructors by specifying the name with list of arguments in parantheses that matches the constructor which is called, (ie) placing a call for the constructor with required number of arguments
    class foo{
        foo() : foo(value) {}   // foo() calls foo(T val) with 'value' to construct the object 
        foo(T val) {}           // foo(T val) is delegated constructor for foo(), where foo() is the delegating constructor
    } 
    Body of foo() will be executed after foo(T val) and its body is finished executing
## Access Specifier
    public : 
        members following public keyword up to any other access specifier can be accessed from any part of the user program.
        They along with some non-member function form the interface of the class.
    private :
        members following private keyword up to any other access specifier can be accessed by only member funtions not the user code.
        They form the implementation part of the class
    friend : 
        For the non-member functions to access non-public members of the class they need to declared as 'friend' to the class
        'friend' declarations should appear inside the class definition, 
        A class allows another class and functions to have access to its non-public members by making them its friend
        friend declarations are not affected by access specifiers.

    --------------------------------example----------------------------------------------------------------------------------

    class foo{
    friend r_type non_memFunc1( para_list );
    public : 
        foo() = default;
        foo( para_list ) : member1( param_1), member2( param_2) {}
        r_type memFunc1( para_list );
        r_type memFunc2( para_list );
    private : 
        member1;
        member2;
    };

    r_type non_memberFunc1( para_list){
        fooObj_para.member1;            //  ok : non_memberFunc1 is declared as friend by foo
        fooObj_para.member2;            //  ok : non_memberFunc1 is declared as friend by foo
    }

    r_type non_memFunc2( para_list){
        fooObj_para.member1;            //  error : non_memFunc2 is not a friend of foo, thought fooObj is accessing its    
                                                    member, member1 is defined as private, so code outside the class 
                                                    defintion is not allowd access
        fooObj_para.member2;            //  error : non_memFunc2 is not a friend of foo, member2 is declared as private
    }

    int main(){
        foo f1;                         //  instantiated by default constructor
        foo f2(arg_list)                //  instantiated by the constructor which takes arg_list as its parameter
        f1.member1;                     //  error : member1 is declared private, code outside the class have no access
        f1.memFunc1(arg_list)           //  ok : memFuc1 is declared public
    }

    -----------------------------example ends here --------------------------------------------------------------------------

### name look up in class
    Normally, name lookup(the process of finding which declarations matches the use of a name) is simple.
        First compiler will look for the name in the in the block in which the name was used but names declared only before the use are conidered.
        If name isn't found, looks in the enclosing scope, again only names declared before the inner scope is considered.
        If no declaration found, then code is in error
    But classes are special, classe definitions are processed in two phases
    1. first the member declarations are compiled
    2. Function bodies are compiled only after entire class is seen
    so function bodies can use any member name regardless of where they are declared
    But for names used in declarations of members, parameters of functions and return types, should be seen before they are used
        when a name is seen, any declarations only before the use in class will be considered, if not found the enclosing scope will be searched but only declarations before the name usage will be considered
#### Type names cannot be redefined in class 
    Ordinarily inner-scope can redefine the names from an outer-scope even if the name is used already in the innerscope.
    ex :-
        int n = 10;
        typedef double price;
        void func(){
            int ivar = n;           // n defined in outer scope
            price pvar = 4.5;       // price defined in outer scope

            int n = -19;            // n redefined in inner scope
            ivar = n;               // n defined in inner scope

            typedef string price;   // price redefined in inner scope
            std::cout << price("hello world") << std::endl;
        }      
    However it is not the case in class defintions
        if a class uses a name from an outer scope and that name is a type, then the class may not subsequently redefine that name
    ex 1 :-
        typedef std::string price;
        class foo{
            private: 
                price val;
                typedef double price;   //  it is in error, as the name price is already in use
        };
    ex 2 :-
        typedef std::string price;
        class foo{
            private:
                typedef double price;
                price val;          //  it is perfectly ok, as the name as been rededined before its use
        };
[stackoverflow : type redefinition inside class](https://stackoverflow.com/questions/45384956/why-cant-redefine-type-names-in-class-in-c)
    
### Special members
#### mutable
    A data member that is never const, that is can be modified even in a const object. A class declares such data member as mutable, that is they are never const
#### Static members 
    static members are data members and member functions that belongs to the class, they exist independently of the object. 
    When a class needs a data member to be shared among all objects, they declare such member as static.
    static members are created in gobal space not in objects memory.
    As they reside seperatly in global space, they don't increase class size, their size don't have any effect in object's size
    A class can have a static data member of its own type, as they are not included in object   