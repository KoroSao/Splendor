#include <iostream>

//#include "../src/controleur/controleur.h"
#include "../src/carte/carte.h"
#include "../src/jeu/jeu.h"
#include "../src/pioche/pioche.h"
#include "../src/niveau/niveau.h"
#include "../src/plateau/plateau.h"

using namespace Splendor;

int main(){
    std::cout << "Hello World !" << std::endl;

    /*
    array<int, 5> cArray = {3, 4, 5, 3, 1};
    array<int, 5> bArray = {0, 0, 0, 1, 0};
    CarteDeveloppement c(cArray, bArray, Type::un, 4);

    std::cout << "c : " << c.getPDV() << std::endl;

    std::cout << Jeu::getInstance().getNbCartes(Type::un) << std::endl;

    Jeu::getInstance().getCartes(Type::un)[0]->getCouts(4);

    Jeu::getInstance().getCartes(Type::un)[0]->afficherCarte();

    Pioche p(Type::un);
    std::cout << "nbr de carte dans la pioche : "<< p.getNbCartes() << std::endl;

    p.piocher().afficherCarte();

    std::cout << "nbr de carte dans la pioche : "<< p.getNbCartes() << std::endl;
    */

    //Création d'un niveau de cartes de type un.
    // Niveau n(4,Type::un);
    // std::cout << n.getTaille() << std::endl;

    // std::cout << "###### Carte dans le niveau initial : ######" << std::endl;
    // n.afficherNiveau();

    // n.retirerCarte(*n.getCartes()[3]);

    // //n.ajouterCarte(n.getPioche().piocher());

    // //n.ajouterCarte(n.getPioche().piocher());

    // std::cout << "###### Carte dans le niveau après piocher : #######" << std::endl;
    // n.afficherNiveau();

    Plateau p(4);
    //p.printBanque();

    //p.getCartesNobles().afficherNiveau();
    // p.getNiveauDeveloppement(0).afficherNiveau();
    // p.getNiveauDeveloppement(1).afficherNiveau();
    // p.getNiveauDeveloppement(2).afficherNiveau();

    p.printPlateau();


    return 0;
}


//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/controleur/controleur.cpp ../src/jeu/jeu.cpp ../src/joueur/joueur.cpp ../src/niveau/niveau.cpp ../src/plateau/plateau.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp -o main && ./main

//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/niveau/niveau.cpp ../src/jeu/jeu.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp ../src/plateau/plateau.cpp -o main && ./main