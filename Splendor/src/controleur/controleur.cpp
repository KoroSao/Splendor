#include "controleur.h"

namespace Splendor{


    Controleur::Controleur(): nbJoueurs(4), plateau(4) { //mettre Controleur(int n=0) : nbJoueurs(n), plateau(n) ??

        //puis adapter

        //Init joueurs vector
        //TODO: appeler à la place de la loop le menu de création d'une partie
        joueurs.push_back(new Joueur(0, "player1"));
        joueurs.push_back(new Joueur(1, "player2"));
        joueurs.push_back(new Joueur(2, "player3"));
        joueurs.push_back(new Joueur(3, "player4"));
    }

    Joueur& Controleur::getJoueur(unsigned int i) {
        if (i >= nbJoueurs || i < 0 )
            throw SplendorException("Splendor::Controleur::getJoueur() : indice i invalide");
        return *joueurs[i];
    }
}
