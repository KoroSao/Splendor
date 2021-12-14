#include "controleur.h"

namespace Splendor{


    Controleur::Controleur(unsigned int nbj): nbJoueurs(nbj), plateau(nbj) {
        //Init joueurs vector
        //TODO: appeler à la place de la loop le menu de création d'une partie
        for (size_t i = 0; i < nbj; i++) {
            string playerName;
            cout << "Please enter player number " << i << " name :";
            std::cin >> playerName;
            joueurs.push_back(new Joueur(i, playerName));
        }
    }


    Joueur& Controleur::getJoueur(unsigned int i) {
        if (i >= nbJoueurs || i < 0 )
            throw SplendorException("Splendor::Controleur::getJoueur() : indice i invalide");
        return *joueurs[i];
    }


}