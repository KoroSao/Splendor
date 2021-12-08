#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>

#include "../carte/carte.h"
#include "../jeu/jeu.h"
#include "../joueur/joueur.h"
#include "../niveau/niveau.h"
#include "../plateau/plateau.h"
#include "../splendorException/splendorexception.h"
#include "../type/type.h"


namespace Splendor{

    class Plateau{

    };

    class Joueur{

    };

    class Jeu{

    };



    class Controleur{
        private:

            struct Handler{
                Controleur* instance;
                Handler():instance(nullptr) {}
            };
            static Handler handler;

            Controleur() = default;
            ~Controleur() = default;
            Controleur(const Controleur&) = delete;
            Controleur& operator=(const Controleur&) = delete;

            //Attributes
            unsigned int nbJoueurs;
            Plateau plateau;
            Joueur** joueurs;
            Jeu jeu;

        public:
            int getNbJoueurs() const { return nbJoueurs; }
            static Controleur& getInstance();
            static void freeInstance();
            Plateau& getPlateau();
    };
}
 

#endif