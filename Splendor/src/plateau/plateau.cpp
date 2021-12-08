#include "plateau.h"


namespace Splendor{

    /*  ============================================================================
                                         CLASS PLATEAU
        ============================================================================ */

    
    Plateau::Plateau(int nb_joueurs): niveaux(new Niveau*[3]) {
        /*
        FAIRE ATTENTION, LA PLUPART DES ATTRIBUTS DU PLATEAU DEPENDENT
        DES VARIABLES D'ENVIRONNEMENT DU JEU COMME LE NOMBRE DE JOUEURS
        LA CREATION DU PLATEAU SE FAIT DONC APRES LES INFORMATIONS
        ESSENTIELS SAISIES PAR LES JOUEURS.
        */
        //Initatialisation de la banque
        banque[5] = 5;
        switch(nb_joueurs){
            case 2:
                for (size_t i = 0; i < 5; i++)
                    banque[i] = 4;
                break;
            case 3:
                for (size_t i = 0; i < 5; i++)
                    banque[i] = 5;
                break;
            default:
                for (size_t i = 0; i < 5; i++)
                    banque[i] = 7;
                break;
        }
        
        
        //Initialisation des Niveaux de cartes Développement
        size_t i = 0;
        for (auto t : Types)
            if (i < 3)
                niveaux[i] = new Niveau(4,t);
        //Initalisation des cartes nobles
        
        cartesNobles = new Niveau(nb_joueurs+1, Type::Noble);
    }


    void Plateau::printBanque(){
        auto banque = getBanque();
        std::cout << "[";
        for (size_t i = 0; i < 5; i++)
            std::cout << banque[i] << ",";
        std::cout << banque[5] << "]";
    }
}