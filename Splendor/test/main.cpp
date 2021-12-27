#include "../src/controleur/controleur.h"

#include "../src/partie/vuePartie.h"

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
    try{
    Controleur c(4);
    for (size_t i = 0; i < c.getNbJoueurs(); i++){
        std::cout << c.getJoueur(i).getNom() ;
        std::cout << c.getJoueur(i).getId() << std::endl;
    }


    //c.getPlateau().printPlateau();
    //c.getJoueur(0).afficherInventaire();
    c.prendreRessource(c.getJoueur(c.getCurrentPlayer()), 0, c.getPlateau());
    c.prendreRessource(c.getJoueur(c.getCurrentPlayer()), 1, c.getPlateau());
    c.prendreRessource(c.getJoueur(c.getCurrentPlayer()), 2, c.getPlateau());
    std::cout << c.getCurrentPlayer() << std::endl;
    std::cout << "Hahaha" << std::endl;
    c.getPlateau().printBanque();
    c.getJoueur(c.getCurrentPlayer()).setInventaire(0,10);
    c.getJoueur(c.getCurrentPlayer()).setInventaire(1,10);
    c.getJoueur(c.getCurrentPlayer()).setInventaire(2,10);
    c.getJoueur(c.getCurrentPlayer()).setInventaire(3,10);
    c.getJoueur(c.getCurrentPlayer()).setInventaire(4,10);

    std::cout << "Cartes avant achat:" << std::endl;
    c.getJoueur(1).afficherCartesRemportees();
    c.selectCarte(c.getJoueur(c.getCurrentPlayer()), c.getPlateau().getNiveauDeveloppement(0).retirerCarte(*c.getPlateau().getNiveauDeveloppement(0).getCartes()[0]), c.getPlateau());
    c.getJoueur(1).afficherCartesRemportees();
    std::cout << c.getCurrentPlayer() << std::endl;
    //c.getJoueur(0).afficherInventaire();

    /*
    typedef array<int, 5> ressources;

    ressources cst = {1,1,1,1,1};
    ressources bns = {0,0,0,0,1};

        
    CarteDeveloppement* cartetest = new CarteDeveloppement(cst, bns, Type::un, 2);
    if(cartetest->canBeBougth(c.getJoueur(0)))
        std::cout << "Achetable" << std::endl;
    std::cout << "Non Achetable" << std::endl;*/
    
    //c.getPlateau().getNiveauDeveloppement(0).getCartes()[0]->afficherCarte();
    
        
        
        // std::cout << "CartesRemportees:" << std::endl;
        // c.getJoueur(0).afficherCartesRemportees();
        // std::cout << "Reserve:" << std::endl;
        // c.getJoueur(0).afficherReserve();
        // c.getJoueur(0).afficherBonus();
    }
    catch(SplendorException& e) { std::cout << e.getInfo() << std::endl;}

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    VuePartie partie;
    partie.show();
    return app.exec();
}


//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/controleur/controleur.cpp ../src/jeu/jeu.cpp ../src/joueur/joueur.cpp ../src/niveau/niveau.cpp ../src/plateau/plateau.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp -o main && ./main

//g++ -std=c++11 main.cpp ../src/controleur/controleur.cpp ../src/carte/carte.cpp ../src/niveau/niveau.cpp ../src/jeu/jeu.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp ../src/plateau/plateau.cpp ../src/joueur/joueur.cpp -o main && ./main
