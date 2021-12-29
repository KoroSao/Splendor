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

namespace Splendor{


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
            void acheterCarte(Joueur& j, const Carte& c);
            void prendreRessource(Joueur& j, unsigned int i);
            void rendreRessource(Joueur&j, unsigned int i);
            void selectCarte(Joueur& j, const Carte&c);

            // ------------ Controle des tours --------------
            void isTurnWithJetonsFinished(Joueur& j);      //Fonction controlant la quantité de jetons pris par le joueur
            bool confirmTurn(Joueur& j);
            void cancelTurn(Joueur& j);
            void endOfTurn(Joueur& j);
            void nextPlayer();
            void endOfGame();

    };

}



#endif
