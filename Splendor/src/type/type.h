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
<<<<<<< HEAD
    enum class Type {nobles=1, cite=2, un=3, deux=4, trois=5 };
    std::string toString(Type c);
=======
    enum class Type {nobles, cite, un, deux, trois};
>>>>>>> cf5867aed5cbec5cb1edc3b8438aedd92fbca79f
    extern std::initializer_list<Type> Types;

    std::string toString(Type type);
}

<<<<<<< HEAD
=======

>>>>>>> cf5867aed5cbec5cb1edc3b8438aedd92fbca79f
#endif
