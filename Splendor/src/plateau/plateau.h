#ifndef _PLATEAU_H
#define _PLATEAU_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>

#include "niveau.h"
#include "../splendorException/splendorexception.h"
#include "../pioche/pioche.h"
#include "../carte/carte.h"
#include "../type/type.h"

using namespace std;

namespace Splendor{



    class Plateau {
        private:

            int banque[6];              //Banque centrale
            Niveau** niveaux;          //Niveaux constituants les rangees de carte
            Niveau* cartesNobles;        //Tableau de pointeurs sur les cartes nobles

        public:
            Plateau(int nbj);
            ~Plateau() = default;
            Plateau(const Plateau&) = delete;
            Niveau& operator[](int i) { return *niveaux[i]; }
            int* getBanque() { return banque; }
            void setBanque(int i, int val) { banque[i] = val; }
            Niveau& getCartesNobles() { return *cartesNobles; }
            void printBanque();
    };

}

#endif 
