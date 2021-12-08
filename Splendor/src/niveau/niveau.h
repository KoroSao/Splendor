#ifndef _NIVEAU_H
#define _NIVEAU_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <initializer_list>
#include <array>

#include "../type/type.h"
#include "../pioche/pioche.h"
#include "../splendorException/splendorexception.h"

using namespace std;

namespace Splendor{

    class Niveau{
        private:
            vector<Carte*> cartes;   //Cartes situées sur un niveau du plateau
            const int nbMax;        //Nombre maximum de cartes maxi sur un niveau (4 pour les cartes dvlp)
            int nb;                 //Nombre de cartes sur le Niveau
            const Type type;        //Type de carte développement situées dans le niveau
            Pioche pioche;          //Pioche associée au type distribuant sur cartes.

        public:
            //Constructor et Destructor
            Niveau(int t, Type ty);
            Niveau& operator=(const Niveau& n) = default;
            Niveau (const Niveau& n) = default;
            ~Niveau() = default;    //vector delete auto ?

            //Getters
            int getTaille() { return nbMax; }
            int getNbCartes() { return nb; }
            Type getType() { return type; }
            Pioche& getPioche() { return pioche; }
            vector<Carte*> getCartes() { return cartes; }    // Renvoie le tableau des cartes

            //Fonctions d'usage
            const Carte& retirerCarte(const Carte& c);      // Retirer une carte du Niveau 
            void ajouterCarte(const Carte& c);              // Ajouter une carte du Niveau
            
            //Utilité d'une méthode pour retourner une carte aléatoire de la pioche ?
            //Sachant que la pioche aura déjà une méthode le faisant.
            //Unique argument valide: interface plus simple avec la classe Niveau.
    };

}
#endif