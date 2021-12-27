#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>
#include <string>

#include "../splendorException/splendorexception.h"

namespace Splendor{

    //enum class Type {I = 1, II = 2, III = 3, Noble = 4};
    enum class Type {nobles=1, cite=2, un=3, deux=4, trois=5 };
    extern std::initializer_list<Type> Types;
    
}

#endif