#ifndef _NIVEAU_H
#define _NIVEAU_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>
#include <algorithm>


#include "../type/type.h"
#include "../pioche/pioche.h"
#include "../splendorException/splendorexception.h"

using namespace std;

namespace Splendor{

    class Niveau{
        private:
            vector<const Carte*> cartes;   //Cartes situées sur un niveau du plateau
            const int nbMax;        //Nombre maximum de cartes sur un niveau (4 pour les cartes dvlp)
            int nb;                 //Nombre de cartes sur le Niveau
            const Type type;        //Type de carte développement situées dans le niveau
            Pioche pioche;          //Pioche associée au type distribuant sur cartes.
            Pioche& getPioche() { return pioche; }
        public:
            //Constructor et Destructor
            Niveau(int t, Type ty);
            Niveau& operator=(const Niveau& n) = delete;
            Niveau (const Niveau& n) = delete;
            ~Niveau() = default;    //vector delete auto ?

            //Getters
            int getTaille() { return nbMax; }
            int getNbCartes() { return nb; }
            Type getType() { return type; }

            vector<const Carte*> getCartes() { return cartes; }    // Renvoie le tableau des cartes

            //Fonctions d'usage
            bool  possedeCarte(const Carte& c);
            const Carte& retirerCarte(const Carte& c);      // Retirer une carte du Niveau 
            void piocherCarte();
            
            //Debug
            void afficherNiveau();
    };

}
#endif
