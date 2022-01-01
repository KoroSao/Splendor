#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <vector>

#include "../carte/carte.h"
#include "../jeu/jeu.h"
#include "../joueur/joueur.h"
#include "../niveau/niveau.h"
#include "../plateau/plateau.h"
#include "../splendorException/splendorexception.h"
#include "../type/type.h"
#include "../renduJetons/vueRenduJetons.h"

/**
* \file controleur.h
* Le code a été réalisé selon l'architecture MVC,
* le contrôleur permet la gestion d'un tour et des différentes actions qui sont associées
* \version 1.0
*/

namespace Splendor{

  /**
  * \class controleur controleur.h
  * Classe qui permet de gérer les actions du joueur et le contrôle des tours
  */
    class Controleur{
        private:
            //Attributes
            unsigned int nbJoueurs;
            Plateau plateau;
            vector<Joueur*> joueurs;
            int currentPlayer;

            bool lastLap = false;


        public:
            friend class VuePartie;
            Controleur(unsigned int nbj, vector<std::string> names);

            ~Controleur() = default;
            Controleur(const Controleur&) = default;
            Controleur& operator=(const Controleur&) = default;

            int getNbJoueurs() const { return nbJoueurs; }
            Plateau& getPlateau() { return plateau; }
            Joueur& getJoueur(unsigned int i);
            int getCurrentPlayer() const { return currentPlayer; }

            // ------------ Action du joueur --------------

            /**
           * \brief Permet d'acheter une carte
           * \param Joueur& j Prend le joueur qui souhaite acheter une carte en paramètre
           */
           void acheterCarte(Joueur& j, const Carte& c);

            /**
           * \brief Permet de prendre un jeton de la i ème ressource à la banque
           */
           void prendreRessource(Joueur& j, unsigned int i);

            /**
           * \brief Permet de rendre qt jetons de la ième ressources à la banque
           */
           void rendreRessource(Joueur&j, unsigned int i, unsigned int qt = 1);

            /**
           * \brief Permet de réserver une carte
           */
           void reserverCarte(Joueur& j, const Carte&c);

            /**
           * \brief Permet de sélectionner une carte afin d'être achetée ou réservée
           */
           void selectCarte(Joueur& j, const Carte&c);


            // ------------ Controle des tours --------------

            /**
           * \brief Permet de controler la quantité de jetons prise par le joueur
           */
          void isTurnWithJetonsFinished(Joueur& j);

          /**
         * \brief Permet de confirmer les actions du tour
         * \return retournera vrai si les actions sont confirmées
         */
          bool confirmTurn(Joueur& j);

          /**
         * \brief Permet d'infirmer les actions du tour
         */
          void cancelTurn(Joueur& j);

          /**
         * \brief C'est la méthode enclenchée à la fin d'un tour afin de vérifier les ressources et d'appeler les cartes spéciales
         */
         void endOfTurn(Joueur& j);

         /**
        * \brief Permet de passer au joueur suivant
        */
         void nextPlayer();

          /**
         * \brief Permet de vérifier si les conditions de victoire sont atteintes et de désigner un vainqueur
         */
         void endOfGame();
         bool getLastLap() {return lastLap; }

    };

}



#endif
