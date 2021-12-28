#include "plateau.h"


namespace Splendor{

    /*  ============================================================================
                                         CLASS PLATEAU
        ============================================================================ */

    
    Plateau::Plateau(int nb_joueurs) : niveaux() {
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
        niveaux.push_back(new Niveau(4,Type::un));
        niveaux.push_back(new Niveau(4,Type::deux));
        niveaux.push_back(new Niveau(4,Type::trois));

        //Initalisation des cartes nobles
        cartesNobles = new Niveau(nb_joueurs+1, Type::nobles);
    }

    Niveau& Plateau::getNiveauDeveloppement(int i) { 
        if(i<0 || i>2){
            throw SplendorException("Splendor::Plateau::getNiveauDeveloppement() : indice i invalide");
        }
        return *niveaux[i]; 
    }

    void Plateau::setBanque(int pos, int val) { 
        if(pos < 0 || pos > 5){
            throw SplendorException("Splendor::Plateau::setBanque() : indice i invalide");
        }
        banque[pos] = val;
    }

    void Plateau::printBanque(){
        auto banque = getBanque();
        std::cout << "[";
        for (size_t i = 0; i < 5; i++)
            std::cout << banque[i] << ",";
        std::cout << banque[5] << "]" << std::endl;
    }

    void Plateau::printPlateau(){
        std::cout << " $ $ $ Banque : $ $ $ " << std::endl;
        printBanque();
        std::cout << std::endl;

        std::cout << " # # # # # # Niveau 3 # # # # # # " << std::endl;
        getNiveauDeveloppement(2).afficherNiveau();

        std::cout << " # # # # # # Niveau 2 # # # # # # " << std::endl;
        getNiveauDeveloppement(1).afficherNiveau();

        std::cout << " # # # # # # Niveau 1 # # # # # # " << std::endl;
        getNiveauDeveloppement(0).afficherNiveau();

        std::cout << " * * * * * * Nobles * * * * * * * *" << std::endl;
        getNiveauNobles().afficherNiveau();

    };
}