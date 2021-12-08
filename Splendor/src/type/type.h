#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>

namespace Splendor{

    //enum class Type {I = 1, II = 2, III = 3, Noble = 4};
    enum class Type {nobles, cite, un=1, deux=2, trois=3 };
    extern std::initializer_list<Type> Types;
    
}

#endif