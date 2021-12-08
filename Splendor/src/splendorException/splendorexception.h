#ifndef SPLENDOREXCEPTION_H
#define SPLENDOREXCEPTION_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>


namespace Splendor{

    //Exception class for the game Splendor
    class SplendorException {
        private:
            std::string info;
        public:
            SplendorException(const std::string & i): info(i) {}
            std::string getInfo() const { return info; }
    };
}
#endif