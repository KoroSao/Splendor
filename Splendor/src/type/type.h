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
    enum class Type {nobles, cite, un, deux, trois};
    std::string toString(Type c);

    extern std::initializer_list<Type> Types;

    std::string toString(Type type);
}

#endif
