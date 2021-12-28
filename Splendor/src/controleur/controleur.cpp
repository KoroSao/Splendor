#include "controleur.h"


namespace Splendor{


    Controleur::Controleur(unsigned int nbj, vector<std::string> names): nbJoueurs(nbj), plateau(nbj), currentPlayer(0), lastLap(false) {
        //Init joueurs vector
        //TODO: appeler à la place de la loop le menu de création d'une partie
        for (size_t i = 0; i < nbj; i++)
            joueurs.push_back(new Joueur(i, names[i]));
    }


    Joueur& Controleur::getJoueur(unsigned int i) {
        if (i >= nbJoueurs || i < 0 )
            throw SplendorException("Splendor::Controleur::getJoueur() : indice i invalide");
        return *joueurs[i];
    }

     /*
            =========================== ACTION DU JOUEUR ==========================
    */

    void Controleur::acheterCarte(Joueur& j, const Carte& c) {
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
    }

    void Controleur::prendreRessource(Joueur& j, unsigned int i) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Joueur::prendreRessource() : indice i, Plateau& p invalide");
        if (!getPlateau().getBanque(i))
            throw SplendorException("Splendor::Joueur::prendreRessource() : Banque vide");
        if (getPlateau().getBanque(i) <= 3 && j.getJetonsPris(i) > 0)
            stopJetons = true;
            //throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 2 jetons d'une pile de moins de 4 de haut");

        tourJeton = true;   //Controle du tour

        int nbJetons = 0;
        for (size_t i = 0; i < 5; i++)
            nbJetons+=j.getJetonsPris(i);
        if(nbJetons == 2 && j.getJetonsPris(i) == 1){
            stopJetons = true;
            //throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 3 jetons non tous différents");
        }

        
        getPlateau().setBanque(i, getPlateau().getBanque(i) - 1); //Retirer un jeton de la banque
        j.setInventaire(i, j.getInventaire(i) + 1); //Ajouter un jeton au joueur
        j.setJetonsPris(i, j.getJetonsPris(i) + 1); //Ajout du jeton à l'historique de jetons du tour
        //isTurnWithJetonsFinished(j);
    }

    void Controleur::rendreRessource(Joueur&j, unsigned int i) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Joueur::prendreRessource() : indice i invalide");
        if (!j.getInventaire(i))
            throw SplendorException("Splendor::Joueur::prendreRessource() : Ressource inexistante");
        j.setInventaire(i, j.getInventaire(i) - 1);       //Retire le jeton de l'inventaire du joueur
        getPlateau().setBanque(i, getPlateau().getBanque(i) + 1);                 //Ajoute le jeton de l'inventaire du joueur dans la banque
    }


    void Controleur::selectCarte(Joueur& j, const Carte& c) {
        if (c.canBeBougth(j)){
            //if (confirmTurn(j)){
                acheterCarte(j,c);
                //endOfTurn(j);
            //}
        } else {
            //if (confirmTurn(j)){
                j.ajouterCarteReserve(c); //Testdans ajouterCarteReserve de la taille de la réserve
                
                if(getPlateau().getBanque(5) > 0){
                    getPlateau().setBanque(5,getPlateau().getBanque(5));
                    j.setInventaire(5,j.getInventaire(5) +1);
                }
                //endOfTurn(j);
            //}
        }
    }

    /*
            =========================== CONTROLE DES TOURS ==========================
    */

  /*
   void Controleur::isTurnWithJetonsFinished(Joueur& j) {
        int nbJetons = 0;
        for (size_t i = 0; i < 5; i++) {
            int x = j.getJetonsPris(i);
            if (x == 2) {
                if (confirmTurn(j))
                    endOfTurn(j);
                else
                    cancelTurn(j);
                break;
            }
            nbJetons += x;
        }
        if (nbJetons == 3){
            if (confirmTurn(j))
                endOfTurn(j);
            else   
                cancelTurn(j);
        }
            
   }

   bool Controleur::confirmTurn(Joueur& j) {
        std::cout << "Confirmez-vous votre action ?" << std::endl;
        int answer;
        std::cin >> answer;
        if (answer == 1)
            return true;
        else
            return false;  
    }

    void Controleur::cancelTurn(Joueur& j) {
        //Méthode permettant de rendre les jetons pris par le joueur
        //quand il cancel son tour
        for (size_t i = 0; i < 5; i++){
            int x = j.getJetonsPris(i);
            for(size_t k = 0; k < x; k++) {
                rendreRessource(j,i);
            }
        }
        //RESET tableau jetonspris
        for (size_t i = 0; i < 5; i++)
            j.setJetonsPris(i,0);
    }
    */
    

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
        if (j.hasVictoryCondition()){
            std::cout << "Last lap" << std::endl;
            lastLap = true;
        }

        //Passer au joueur suivant
        if ((lastLap && currentPlayer != nbJoueurs - 1) || !lastLap)
            nextPlayer();
        else
            endOfGame();
   }

   void Controleur::endOfGame(){
       int joueurGagnant = 0;
       for (unsigned int i = 0; i < nbJoueurs; i++) {
            if (getJoueur(i).getPDV() > getJoueur(i).getPDV()){
                joueurGagnant = i;
            }
       }
       std::cout << "Le joueur gagnant est " << getJoueur(joueurGagnant).getNom() <<std::endl;
       std::cout << "Il remporte la partie avec " << getJoueur(joueurGagnant).getPDV() << "Points de victoire !" << std::endl;
   }



}
