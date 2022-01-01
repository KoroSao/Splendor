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
/**
* \file plateau.h
* Ce fichier permet de gérer les ressouces présentes au niveau du plateau
* \version 1.0
*/
namespace Splendor {

    /**
    * \class Plateau plateau.h
    * Classe qui gère les attributs de la banque notamment
    */
    class Plateau {
        private:
            /**
           * \brief Banque centrale
           */
            int banque[6];
            //Niveau** niveaux;
            /**
           * \brief Niveaux constituants les rangees de carte
           */
            vector<Niveau*> niveaux;
            //Niveau* cartesNobles;
            /**
           * \brief Tableau de pointeurs sur les cartes nobles
           */
            Niveau* cartesNobles;

        public:
            Plateau(int nbj);
            ~Plateau() = default;
            Plateau(const Plateau&) = delete;

            /**
           * \return Retourne un pointeur sur la première case du tableau de la banque centrale
           */
            int* getBanque() { return banque; }
            /**
           * \return Retourne les ressources de la banque centrale pour la ième (pos) catégorie
           */
            int getBanque(unsigned int pos) { return banque[pos]; }
            /**
           * \brief Met la valeur val à la ième (pos) position en terme de ressources pour la banque centrale
           */
            void setBanque(int pos, int val);
            /**
           * \return Retourne une référence sur le niveau des cartes nobles
           */
            Niveau& getNiveauNobles() { return *cartesNobles; }
            /**
           * \return Retourne une référence sur le niveau des cartes de développement de type i
           */
            Niveau& getNiveauDeveloppement(int i);
            /**
           * \brief Fonction qui permet d'afficher les ressouces de la banque
           */
            void printBanque();
            /**
           * \brief Fonction qui permet d'afficher la banque, les différents niveaux de développement et les cartes nobles 
           */
            void printPlateau();
    };

}

#endif
