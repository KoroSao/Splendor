#include <iostream>

//#include "../src/controleur/controleur.h"
#include "../src/carte/carte.h"
#include "../src/jeu/jeu.h"
#include "../src/pioche/pioche.h"
#include "../src/niveau/niveau.h"
#include "../src/plateau/plateau.h"
#include "../src/joueur/joueur.h"
#include "../src/controleur/controleur.h"

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

    // Plateau p(4);
    // //p.printBanque();

    // //p.getCartesNobles().afficherNiveau();
    // // p.getNiveauDeveloppement(0).afficherNiveau();
    // // p.getNiveauDeveloppement(1).afficherNiveau();
    // // p.getNiveauDeveloppement(2).afficherNiveau();

    // // p.printPlateau();
    // Joueur j(0, "AJouglet");
    // j.addPDV(10);
    // std::cout << j.getPDV() << std::endl;
    // j.afficherBonus();
    // j.afficherInventaire();

    // j.setInventaire(0, 3);
    // j.setBonus(3,4);
    // j.setBonus(3, j.getBonus(3) + 2);

    // j.afficherBonus();
    // j.afficherInventaire();

    // j.ajouterCarteReserve(p.getNiveauDeveloppement(0).retirerCarte(*p.getNiveauDeveloppement(0).getCartes()[0]));
    // j.afficherCartesRemportees();
    // j.afficherReserve();

    // std::cout << j.getNom() << std::endl;

    // p.printPlateau();

    Controleur c(4);
    for (size_t i = 0; i < c.getNbJoueurs(); i++){
        std::cout << c.getJoueur(i).getNom() ;
        std::cout << c.getJoueur(i).getId() << std::endl;
    }

    //c.getPlateau().printPlateau();
    c.getJoueur(0).afficherInventaire();
    c.getJoueur(0).prendreRessource(0, c.getPlateau());
    c.getPlateau().printBanque();
    c.getJoueur(0).setInventaire(0,10);
    c.getJoueur(0).setInventaire(1,10);
    c.getJoueur(0).setInventaire(2,10);
    c.getJoueur(0).setInventaire(3,10);
    c.getJoueur(0).setInventaire(4,10);
    c.getJoueur(0).afficherInventaire();

    /*
    typedef array<int, 5> ressources;

    ressources cst = {1,1,1,1,1};
    ressources bns = {0,0,0,0,1};

        
    CarteDeveloppement* cartetest = new CarteDeveloppement(cst, bns, Type::un, 2);
    if(cartetest->canBeBougth(c.getJoueur(0)))
        std::cout << "Achetable" << std::endl;
    std::cout << "Non Achetable" << std::endl;
    */
    c.getPlateau().getNiveauDeveloppement(0).getCartes()[0]->afficherCarte();
    try{
        c.getJoueur(0).selectCarte(c.getPlateau().getNiveauDeveloppement(0).retirerCarte(*c.getPlateau().getNiveauDeveloppement(0).getCartes()[0]), c.getPlateau());
        std::cout << "CartesRemportees:" << std::endl;
        c.getJoueur(0).afficherCartesRemportees();
        std::cout << "Reserve:" << std::endl;
        c.getJoueur(0).afficherReserve();
        c.getJoueur(0).afficherBonus();
    }
    catch(SplendorException& e) { std::cout << e.getInfo() << std::endl;}
    

    return 0;
}


//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/controleur/controleur.cpp ../src/jeu/jeu.cpp ../src/joueur/joueur.cpp ../src/niveau/niveau.cpp ../src/plateau/plateau.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp -o main && ./main

//g++ -std=c++11 main.cpp ../src/controleur/controleur.cpp ../src/carte/carte.cpp ../src/niveau/niveau.cpp ../src/jeu/jeu.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp ../src/plateau/plateau.cpp ../src/joueur/joueur.cpp -o main && ./main