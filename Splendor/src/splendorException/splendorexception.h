#ifndef SPLENDOREXCEPTION_H
#define SPLENDOREXCEPTION_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>

/**
* \file splendorexception.h
* Ce fichier permet de gérer les exceptions 
* \version 1.0
*/
namespace Splendor{

  /**
  * \class SplendorException splendorexception.h
  * Classe qui permet de gérer les exceptions du jeu Splendor
  */
    class SplendorException {
        private:
            std::string info;
        public:
            SplendorException(const std::string & i): info(i) {}
            std::string getInfo() const { return info; }
    };
}
#endif
