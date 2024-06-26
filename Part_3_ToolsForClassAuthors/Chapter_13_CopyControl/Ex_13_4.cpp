/************************************************************************************************************************************************************
 * @file Ex_13_4.cpp
 * @brief Exercise 13.4: Assuming Point is a class type with a public copy constructor, identify each use of the copy constructor
 * in this program fragment:
 *      Point global; 
 *      Point foo_bar(Point arg){
 *          Point local = arg, *heap = new Point(global);
 *          *heap = local;
 *          Point pa[ 4 ] = { local, *heap };
 *          return *heap;
 *      }
 * @date 2024-01-22
 * 
 * @copyright Copyright (c) 2024
 * 
 *************************************************************************************************************************************************************/

/************************************************************************************************************************************************************
 * 1. foo_bar() is called, then copy constructor is used to construct the parameter from the argument
 * 2. copy constructor is used to copy arg in to local
 * 3. Point(global), as global is a Point type, copy constructor is used but still the process is direct initialisation
 * 4. Point pa[4] = {local, *heap};  copy constructor is used to initialise the array, the remaining elements are value initialised
 * 5. return *heap; copy constructor is used to initialise the result of the call expression from the return value
 *************************************************************************************************************************************************************/

