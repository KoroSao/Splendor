#include "controleur.h"

namespace Splendor{


    Controleur::Controleur(unsigned int nbj): nbJoueurs(nbj), plateau(nbj), currentPlayer(0) {
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

     /*
            =========================== ACTION DU JOUEUR ==========================
    */

    void Controleur::acheterCarte(Joueur& j, const Carte& c, Plateau& p) {
        if (!c.canBeBougth(j))
            throw SplendorException("Splendor::Joueur::acheterCarte() : ressources insuffisantes");

        j.addCartesRemportees(c);
        int jetons_manquants = 0;
        
        for (size_t i = 0; i<5;i++){
            jetons_manquants += max(0, c.getCouts(i)-j.getBonus(i)-j.getInventaire(i));
            j.setInventaire(i, max(0,j.getBonus(i)+j.getInventaire(i) - c.getCouts(i))); //Soustrait les jetons
        }

        if(jetons_manquants)
            j.setInventaire(5, j.getInventaire(5) - jetons_manquants);  //soustrait les jokers
    
        try{
            Carte_avec_bonus* cab = dynamic_cast<Carte_avec_bonus*>(const_cast<Carte*>(&c));
            for (size_t i = 0; i<5;i++){
                j.setBonus(i, j.getBonus(i) + cab->getBonus(i) );
            }        
        }catch(SplendorException& e) { std::cout << e.getInfo() << std::endl; }
        endOfTurn(j);
    }

    void Controleur::prendreRessource(Joueur& j, unsigned int i, Plateau& p) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Joueur::prendreRessource() : indice i invalide");
        if (!p.getBanque(i))
            throw SplendorException("Splendor::Joueur::prendreRessource() : Banque vide");
        if (p.getBanque(i) <= 3 && j.getJetonsPris(i) > 0)
            throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 2 jetons d'une pile de moins de 4 de haut");

        int nbJetons = 0;
        for (size_t i = 0; i < 5; i++)
            nbJetons+=j.getJetonsPris(i);
        if(nbJetons == 2 && j.getJetonsPris(i) == 1)
            throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 3 jetons non tous différents");

        
        p.setBanque(i, p.getBanque(i) - 1); //Retirer un jeton de la banque
        j.setInventaire(i, j.getInventaire(i) + 1); //Ajouter un jeton au joueur
        j.setJetonsPris(i, j.getJetonsPris(i) + 1); //Ajout du jeton à l'historique de jetons du tour
        isTurnFinished(j);
    }

    void Controleur::selectCarte(Joueur& j, const Carte& c, Plateau& p) {
        if (c.canBeBougth(j)){
            acheterCarte(j,c,p);
        } else {
            j.ajouterCarteReserve(c); //Testdans ajouterCarteReserve de la taille de la réserve
            endOfTurn(j);
        }
    }

    /*
            =========================== CONTROLE DES TOURS ==========================
    */

   void Controleur::isTurnFinished(Joueur& j) {
        int nbJetons = 0;
        for (size_t i = 0; i < 5; i++) {
            int x = j.getJetonsPris(i);
            if (x == 2) 
                endOfTurn(j);
            nbJetons += x;
        }
        if (nbJetons == 3)
            endOfTurn(j);
   }

   void Controleur::nextPlayer() {
        currentPlayer++;
        if (currentPlayer >= nbJoueurs)
            currentPlayer = 0;
   }

   void Controleur::endOfTurn(Joueur& j) {
       std::cout << "Fin de ton tour !" << std::endl;

       //RESET tableau jetonspris
       for (size_t i = 0; i < 5; i++)
           j.setJetonsPris(i,0);

       //Check si trop de ressources (demander d'en surppirmer)
       if (j.inventaireFull()){
           std::cout << "Il faut vider ton inventaire" << std::endl;
       }

       //Check les cartesnobles
        for (size_t i = 0; i < nbJoueurs + 1; i++){
            if (getPlateau().getNiveauNobles().getCartes()[i]->canBeBougth(j))
                j.addCartesRemportees(*getPlateau().getNiveauNobles().getCartes()[i]);
        }

        //Check victory
        if (j.hasVictoryCondition())
            std::cout << "Last lap !" << std::endl;

        //Passer au joueur suivant
        nextPlayer();
   }



}