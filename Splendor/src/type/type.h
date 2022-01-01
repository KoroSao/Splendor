#ifndef TYPE_H
#define TYPE_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>
#include <string>

#include "../splendorException/splendorexception.h"

/**
* \file type.h
* Ce fichier définit des structures nécessaires au jeu
* \version 1.0
*/

namespace Splendor{

    //enum class Type {I = 1, II = 2, III = 3, Noble = 4};
    /**
    * \struct Type type.h
    * \brief Permet de définir les différentes cartes de développement (niveau 1, 2 et 3) ainsi que les cartes spéciales (nobles et cité)
    */
    enum class Type {nobles, cite, un, deux, trois};
    std::string toString(Type c);

    extern std::initializer_list<Type> Types;

}

#endif
