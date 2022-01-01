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

/**
* \file niveau.h
* Ce fichier permet de gérer les actions sur les cartes en fonction de leurs niveaux, il permet d'avoir une vue d'ensemble sur les différentes catégories
* \version 1.0
*/

namespace Splendor{

    /**
    * \class niveau niveau.h
    * Permet de gérer les cartes en fonction de leurs niveaux
    */
    class Niveau{
        private:
            /**
           * \brief Cartes situées sur un niveau du plateau
           */
            vector<const Carte*> cartes;
            /**
           * \brief Nombre maximum de cartes sur un niveau (4 pour les cartes dvlp)
           */
            const int nbMax;
            /**
           * \brief Nombre de cartes sur le Niveau
           */
            int nb;
            /**
           * \brief Type de carte développement situées dans le niveau
           */
            const Type type;
            /**
           * \brief Pioche associée au type distribuant sur cartes
           */
            Pioche pioche;

        public:
            //Constructor et Destructor
            Niveau(int t, Type ty);
            Niveau& operator=(const Niveau& n) = delete;
            Niveau (const Niveau& n) = delete;
            /**
           * \brief Pas besoin de libérer la mémoire dans le destructeur grâce à la structure de vecteur
           */
            ~Niveau() = default;

            //------------------------------Getters----------------------------------------------------
            /**
           * \return Renvoie le nombre maximum de cartes d'un niveau
           */
            int getTaille() { return nbMax; }
            /**
           * \return Renvoie le nombre de cartes d'un niveau
           */
            int getNbCartes() { return nb; }
            /**
           * \return Renvoie le type de la carte (niveau 1, 2 ou 3)
           */
            Type getType() { return type; }
            /**
           * \brief La fonction doit être publique pour piocher une carte à réservé
           *  \return Renvoie une référence sur la pioche associée
           */
            Pioche& getPioche() { return pioche; }
            /**
           * \return Renvoie le tableau des cartes
           */
            vector<const Carte*> getCartes() { return cartes; }

            //----------------------------------Setters----------------------------------------------------
            /**
           * \brief La fonction remplace le nombre de cartes d'un niveau par la valeur i
           */
            void setNbCartes(unsigned int i) { nb=i; }

            //----------------------------Fonctions d'usage-------------------------------------------------
            /**
           * \brief La fonction permet de savoir si une carte peut être trouvée par l'itérateur et donc être possedée
           * \return Renvoie true si la carte peut être possédée et false sinon
           */
            bool  possedeCarte(const Carte& c);
            /**
           * \brief La fonction permet de retirer une carte du Niveau
           */
            const Carte& retirerCarte(const Carte& c);
            /**
           * \brief La fonction permet de prendre une carte à la pioche associée
           */
            void piocherCarte();

            //Debug
            /**
           * \brief La fonction permet d'afficher les cartes du niveau
           */
            void afficherNiveau();
    };
}
#endif
