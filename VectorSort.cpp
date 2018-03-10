#include <iostream>  
#include <vector>  
#include <algorithm>  
#include "find_dup.hpp"
using namespace std;
//define sort based on size
bool SortBySize( My_File &v1, My_File &v2)
{  
    return v1.size < v2.size;  
} 
