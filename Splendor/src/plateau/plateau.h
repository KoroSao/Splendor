#ifndef _PLATEAU_H
#define _PLATEAU_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>
#include <vector>

#include "../niveau/niveau.h"
#include "../splendorException/splendorexception.h"
#include "../pioche/pioche.h"
#include "../carte/carte.h"
#include "../type/type.h"

using namespace std;

namespace Splendor {

    class Plateau {
        private:
            int banque[6];                    //Banque centrale
            //Niveau** niveaux;          
            vector<Niveau*> niveaux;          //Niveaux constituants les rangees de carte
            //Niveau* cartesNobles;        
            Niveau* cartesNobles; //Tableau de pointeurs sur les cartes nobles

        public:
            Plateau(int nbj);
            ~Plateau() = default;
            Plateau(const Plateau&) = delete;
            int* getBanque() { return banque; }
            int getBanque(unsigned int pos) { return banque[pos]; }
            void setBanque(int pos, int val);
            Niveau& getNiveauNobles() { return *cartesNobles; }
            Niveau& getNiveauDeveloppement(int i);
            void printBanque();
            void printPlateau();
    };

}

#endif 
