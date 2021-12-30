#include "controleur.h"
#include <sstream>

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
        if (!c.canBeBougth(j)){
            std::string infos = "Splendor::Controleur::acheterCarte() : ressources insuffisantes \n";
            infos+= "Couts carte : ";
            for (size_t i = 0; i<5; i++) infos += to_string(c.getCouts(i));
            infos += "\nInventaire joueur :";
            for (size_t i =0; i<6; i++) infos += to_string(j.getInventaire(i));
            infos += "\n";
            throw SplendorException(infos);
        }

        CarteDeveloppement* c_dev = dynamic_cast<CarteDeveloppement*>(const_cast<Carte*>(&c));
        if(c_dev){

            //on réalise la transaction entre la banque et le joueur
            //on utilise uniquement les jokers comme supplement en cas de manque
            unsigned int jetons_manquants = 0;
            for (size_t i = 0; i<5; i++){
                if(c_dev->getCouts(i)!=0){
                    unsigned int cout_moins_bonus = (unsigned int)max(0, (int)(c_dev->getCouts(i)-j.getBonus(i)));
                    unsigned int qt_depense = min(j.getInventaire(i), cout_moins_bonus);
                    rendreRessource(j, i, qt_depense);
                    jetons_manquants += cout_moins_bonus-qt_depense;
                }
            }
            rendreRessource(j, 5, jetons_manquants);


            int i_type = -1;
            switch (c_dev->getType()) {
                case Type::un:
                    i_type = 0;
                break;
                case Type::deux:
                    i_type = 1;
                break;
                case Type::trois:
                    i_type = 2;
                break;
                default:
                    std::stringstream infos;
                    infos << "Splendor::Controleur::reserverCarte : Type d'une carte Developement inconnu" << endl;
                    infos << "c_dev.getType() :" << toString(c_dev->getType());
                    throw SplendorException(infos.str());
                break;
            }
            //Au cas où la carte viens des cartes reservé par le joueur
            if (plateau.getNiveauDeveloppement(i_type).possedeCarte(*c_dev)){
                plateau.getNiveauDeveloppement(i_type).retirerCarte(*c_dev);
            }
            else{//la carte ne vient pas du plateau donc de la main du joueur
                j.retirerCarteReserve(*c_dev);
            }

            j.addCartesRemportees(c);
            for (size_t i = 0; i<5;i++){
                j.setBonus(i, j.getBonus(i) + c_dev->getBonus(i) );
            }
            j.addPDV(c_dev->getPDV());
        }
        else throw SplendorException("Splendor::Controleur::acheterCarte  : type de carte non supporté");
    }

    void Controleur::prendreRessource(Joueur& j, unsigned int i) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Joueur::prendreRessource() : indice i, Plateau& p invalide");
        if (!getPlateau().getBanque(i))
            throw SplendorException("Splendor::Joueur::prendreRessource() : Banque vide");
        /*if (getPlateau().getBanque(i) <= 3 && j.getJetonsPris(i) > 0)
            stopJetons = true;
            //throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 2 jetons d'une pile de moins de 4 de haut");

        tourJeton = true;   //Controle du tour

        int nbJetons = 0;
        for (size_t i = 0; i < 5; i++)
            nbJetons+=j.getJetonsPris(i);
        if(nbJetons == 2 && j.getJetonsPris(i) == 1){
            stopJetons = true;
            //throw SplendorException("Splendor::Joueur::prendreRessources() : Impossible de prendre 3 jetons non tous différents");
        }*/

        
        getPlateau().setBanque(i, getPlateau().getBanque(i) - 1); //Retirer un jeton de la banque
        j.setInventaire(i, j.getInventaire(i) + 1); //Ajouter un jeton au joueur
        j.setJetonsPris(i, j.getJetonsPris(i) + 1); //Ajout du jeton à l'historique de jetons du tour
        //isTurnWithJetonsFinished(j);
    }

    void Controleur::rendreRessource(Joueur&j, unsigned int i, unsigned int qt) {
        if(i > 5 || i < 0){
            std::stringstream infos;
            infos << "Splendor::Controleur::rendreRessource() : indice i invalide";
            infos << std::endl << "i : "<< i;
            throw SplendorException(infos.str());
        }
        if (j.getInventaire(i)<qt){
            std::cout << "Erreur : " <<qt << std::endl;
            std::stringstream infos;
            infos << "Splendor::Controleur::rendreRessource() : Ressource insuffisante";
            infos <<std::endl<<"Quantité dans inventaire : "<<j.getInventaire(i)<<std::endl;
            infos <<std::endl<<"Quantité demandé au retrait : "<<qt<<std::endl;
            throw SplendorException(infos.str());
        }
        if (qt == 0) return;
        j.setInventaire(i, j.getInventaire(i) - qt);       //Retire le jeton de l'inventaire du joueur
        getPlateau().setBanque(i, getPlateau().getBanque(i) + qt);                 //Ajoute le jeton de l'inventaire du joueur dans la banque
    }


    void Controleur::reserverCarte(Joueur& j, const Carte&c){
        j.ajouterCarteReserve(c);
        if (getPlateau().getBanque(5)>0){
            j.setInventaire(5, j.getInventaire(5)+1);//donne un joker si il y en a encore
            plateau.setBanque(5, plateau.getBanque(5)-1);
        }
        CarteDeveloppement* c_dev = dynamic_cast<CarteDeveloppement*>(const_cast<Carte*>(&c));
        if(c_dev){
            int i_type = 0;
            switch (c_dev->getType()) {
                case Type::un:
                    i_type = 0;
                break;
                case Type::deux:
                    i_type = 1;
                break;
                case Type::trois:
                    i_type = 2;
                break;
                default:
                    std::stringstream infos;
                    infos << "Splendor::Controleur::reserverCarte : Type d'une carte Developement inconnu" << endl;
                    infos << "c_dev.getType() :" << toString(c_dev->getType());
                    throw SplendorException(infos.str());
                break;
            }
            //Au cas où la carte viens d'une pioche, on a pas besoin de la retirer d'un niveau
            if (plateau.getNiveauDeveloppement(i_type).possedeCarte(*c_dev)){
                plateau.getNiveauDeveloppement(i_type).retirerCarte(*c_dev);
            }
        }
        else throw SplendorException("Splendor::Controleur::acheterCarte  : type de carte non supporté");
    }

    void Controleur::selectCarte(Joueur& j, const Carte& c) {

        if (c.canBeBougth(j)){
            acheterCarte(j,c);
        } else {
            reserverCarte(j, c);
        }
    }

    /*
            =========================== CONTROLE DES TOURS ==========================
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
           VueRenduJetons* rendu = new VueRenduJetons(&getJoueur(getCurrentPlayer()));
           rendu->show();
       }

       //Check les cartesnobles
        for (size_t i = 0; i < getPlateau().getNiveauNobles().getCartes().size(); i++){
            if (getPlateau().getNiveauNobles().getCartes()[i]->canBeBougth(j)){

                j.addCartesRemportees(*getPlateau().getNiveauNobles().getCartes()[i]);
                try{
                    CarteNoble* cn = dynamic_cast<CarteNoble*>(const_cast<Carte*>(getPlateau().getNiveauNobles().getCartes()[i]));
                    j.addPDV(cn->getPDV());
                }catch(SplendorException& e) { std::cout << e.getInfo() << std::endl; }
                getPlateau().getNiveauNobles().retirerCarte(*getPlateau().getNiveauNobles().getCartes()[i]);
            }
        }

        //Check victory
        if (j.hasVictoryCondition()){
            std::cout << "Last lap" << std::endl;
            lastLap = true;
        }

        //fin de partie
        if (lastLap && currentPlayer == nbJoueurs - 1)
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
