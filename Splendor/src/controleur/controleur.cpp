#include "controleur.h"


namespace Splendor{


    Controleur::Controleur(unsigned int nbj, vector<std::string> names): nbJoueurs(nbj), plateau(nbj), currentPlayer(0), lastLap(false) {
        //Init joueurs vector
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

        CarteDeveloppement* c_dev = dynamic_cast<CarteDeveloppement*>(const_cast<Carte*>(&c));
        if(c_dev){

            //on réalise la transaction entre la banque et le joueur
            //on utilise uniquement les jokers comme supplement en cas de manque
            size_t jetons_manquants = 0;
            size_t qt_depense = 0;
            for (size_t i = 0; i<5; i++){
                qt_depense = min(j.getInventaire(i), c.getCouts(i)-j.getBonus(i));
                rendreRessource(j, i, qt_depense);
                jetons_manquants += qt_depense-c.getCouts(i)-j.getBonus(i);
            }
            rendreRessource(j, 5, jetons_manquants);



            switch (c_dev->getType()) {
                case Type::un:
                    plateau.getNiveauDeveloppement(0).retirerCarte(*c_dev);
                break;
                case Type::deux:

                    plateau.getNiveauDeveloppement(1).retirerCarte(*c_dev);
                break;
                case Type::trois:
                    plateau.getNiveauDeveloppement(2).retirerCarte(*c_dev);
                break;
            }

            j.addCartesRemportees(c);
            for (size_t i = 0; i<5;i++){
                j.setBonus(i, j.getBonus(i) + c_dev->getBonus(i) );
            }
            j.addPDV(c_dev->getPDV());
        }
        else
            throw SplendorException("Splendor::Controleur::acheterCarte  : type de carte non supporté");
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

    void Controleur::rendreRessource(Joueur&j, unsigned int i, size_t qt) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Controleur::prendreRessource() : indice i invalide");
        if (!j.getInventaire(i))
            throw SplendorException("Splendor::Controleur::prendreRessource() : Ressource inexistante");
        if (j.getInventaire(i)<qt)
            throw SplendorException("Splendor::Controleur::prendreRessource() : Ressource insuffisante");
        j.setInventaire(i, j.getInventaire(i) - qt);       //Retire le jeton de l'inventaire du joueur
        getPlateau().setBanque(i, getPlateau().getBanque(i) + qt);                 //Ajoute le jeton de l'inventaire du joueur dans la banque
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
                    getPlateau().setBanque(5,getPlateau().getBanque(5) - 1);
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
