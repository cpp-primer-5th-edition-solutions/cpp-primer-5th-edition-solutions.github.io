# <p style="text-align:center">ASSOCIATIVE CONTAINERS</p>
    Associative containers stores the elements based on the values of keys, ordered types stores their elements in order by comparing the keys using '<' operator defined by key type. Unordered types uses hashes for the keys to store the elements in buckets for faster average access time. There are totaly eight types
1. map  
2. set
3. multi_map
4. multi_set
5. unordered map
6. unordered set
7. unordered multi_map
8. unordered multi_set

## map and set contains unique keys
## map : stores elements of pair type, std::map<T1, T2>  : T1 maps to T2, key = T1,  value = T2
- elements are key-value pairs 
- keys are compared using '<' operator, so key type should have defined '<' operator or we should provide comparison function to compare the keys.
    * if a key is lesser than the other, then 2nd key should not be lesser than 1st
    * if two keys are not lesser than each other, then they are considered equal
    * if 1st key is lesser than the 2nd and if 2nd is lesser than the 3rd, then 1st is lesser than 3rd
    * if 1st key is equal to 2nd and 2nd is equal to 3rd, then 1st is equal to 3rd
- [] operator supported, keys are the index in to the map, when keys are subscripted, [] operator returns the value associated with the key of the element for which the key matches, or else a new element is constructed with key and value part value initialised and inserted in to the map and then returns value part 
- as keys acts as index in to the map, they are const by default, we can only change the value associated with it.
- iterators points to the element in the map, which is a pair type, so on dereferencing returns a pair type consisting of const key and value of the element
    ex:- std::map<T1, T2> m;
        auto iter = m.begin();
        std::pair<const T1, T2> p = *iter;

## set : key is the element's value, std::set<T> 
- elements are not pairs, key is the element's value
- elements are stored in the same way as maps
- since the elements are ordered, finding a key in a set is quick operation compared to other containers

## Adding elements
- insert memeber inserts elements in to the containers
- set : insert takes an argument of key type, 
    * if the key is present it does nothing
    * key is added otherwise
- map : insert takes an argument of pair type which should match with the pair type of the element in the map
    * [key] returns the reference to the value associated with key, which can be used to change the value part, is key is not present, a new element is constructed with key as key_part and value value-initialised, returns the reference to the value
    * return a pair type consisting of iter, and a bool indicating result of insertion
    * if key is present, iter points to the element whose key matches with the key passed and bool type will be false to indicated insertion didn't happen as key is already present
    * if key is not present, a new element is constructed with key and value intialised with value-initialisation and inserted. iter will point to the new element and bool will be true indicating success

## multimap and multiset
- keys can be repeated
- no [] operator, as there may be many keys with same value
- keys with same value are stored adjusent to each other, their order will be based on the insertion order
- insert member always inserts the key even if key and value are same 

# PAIR type : std::pair<T1, T2>
- pair type is a library type which has two public members named first and second, both need not be the same type
    * pairObj.first = first member
    * pairObj.second = second member
- construction
    * {T1,T2} : brace initialisation
    * std::make_pair(T1,T2) : returns a pair_type containing T1 as first and T2 as second
    * std::pair<T1,T2>(t1,t2) : t1, t2 are objects of T1, T2 type respectively

## unordered maps and unordered sets
- elements are unordered,Unordered containers use the key type’s == operator and an object of type hash<key_type> to organize their elements.
- elements are stored in different buckets, based on the hash codes and '==' operator is used for comparing keys
- hash code is generated against the keys, key are accordingly stored in buckets
    * hash code should be same for keys with same value
    * library provides hash functions for all bult-in types and some library types like strings
- for class types, we must provide hash function and a equality comparison function if '==' is not defined
- provides faster average access times for elements, as they are stored in different buckets
- when storing elements in sorted is prohibitive and there is no natural way to compare elements, then unordered types are best used
- supports all operations of their ordered ones





