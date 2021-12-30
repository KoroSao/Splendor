#include <iostream>
#include <QStyleFactory>
#include <QApplication>
#include <QDebug>

//#include "../src/controleur/controleur.h"
#include "../src/carte/carte.h"
#include "../src/jeu/jeu.h"
#include "../src/pioche/pioche.h"
#include "../src/niveau/niveau.h"
#include "../src/plateau/plateau.h"
#include "../src/joueur/joueur.h"
#include "../src/controleur/controleur.h"

#include "../src/partie/vuePartie.h"
#include "../src/menu/vueNumberOfPlayers.h"

using namespace Splendor;

int main(int argc, char* argv[]){
    unsigned int nbj = 4;
    vector<std::string>names;
    names.push_back("Arthur");
    names.push_back("Emma");
    names.push_back("Francois");
    names.push_back("Romain");
    /*
    try{
    Controleur c(4, names);
    for (size_t i =0; i<5; i++) c.getJoueur(c.getCurrentPlayer()).setInventaire(i, 5);
    const Carte* crt = c.getPlateau().getNiveauDeveloppement(0).getCartes()[0];
    std::cout << "carte dev niv I : " << std::endl;
    c.getPlateau().getNiveauDeveloppement(0).afficherNiveau();
    std::cout << "Inventaire Joueur : " << std::endl;
    c.getJoueur(c.getCurrentPlayer()).afficherInventaire();
    std::cout << "Carte a acheter" << std::endl;
    crt->afficherCarte();

    c.acheterCarte(c.getJoueur(c.getCurrentPlayer()), *crt);
    std::cout << "Achat realise !"<<std::endl;
    std::cout <<"carte dev niv I :"<<std::endl;
    c.getPlateau().getNiveauDeveloppement(0).afficherNiveau();
    std::cout << "carte achetee par le joueur : "<<std::endl;
    c.getJoueur(c.getCurrentPlayer()).afficherCartesRemportees();

    for (size_t i =0; i<5; i++) c.getJoueur(c.getCurrentPlayer()).setInventaire(i, 5);
    crt = c.getPlateau().getNiveauDeveloppement(0).getCartes()[0];
    std::cout << "carte dev niv I : " << std::endl;
    c.getPlateau().getNiveauDeveloppement(0).afficherNiveau();
    std::cout << "Inventaire Joueur : " << std::endl;
    c.getJoueur(c.getCurrentPlayer()).afficherInventaire();
    std::cout << "Bonus Joueur : " << std::endl;
    c.getJoueur(c.getCurrentPlayer()).afficherBonus();
    std::cout << "Carte a acheter" << std::endl;
    crt->afficherCarte();

    c.acheterCarte(c.getJoueur(c.getCurrentPlayer()), *crt);
    std::cout << "Achat realise !"<<std::endl;
    std::cout <<"carte dev niv I :"<<std::endl;
    c.getPlateau().getNiveauDeveloppement(0).afficherNiveau();
    std::cout << "carte achetee par le joueur : "<<std::endl;
    c.getJoueur(c.getCurrentPlayer()).afficherCartesRemportees();
    }
    catch(const SplendorException& e){
        std::cout << e.getInfo()<<endl;
    }
    */
    QApplication app(argc, argv);
    QApplication::setStyle("Fusion");


    VuePartie partie(nbj,names);
    partie.show();

    /*
    vueNumberOfPlayers menu;
    menu.show();*/
    return app.exec();
}


//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/controleur/controleur.cpp ../src/jeu/jeu.cpp ../src/joueur/joueur.cpp ../src/niveau/niveau.cpp ../src/plateau/plateau.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp -o main && ./main

//g++ -std=c++11 main.cpp ../src/controleur/controleur.cpp ../src/carte/carte.cpp ../src/niveau/niveau.cpp ../src/jeu/jeu.cpp ../src/type/type.cpp ../src/pioche/pioche.cpp ../src/plateau/plateau.cpp ../src/joueur/joueur.cpp -o main && ./main
