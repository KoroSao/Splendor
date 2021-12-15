#include "joueur.h"

namespace Splendor {

    /*
            =========================== GETTERS ===========================
    */
    int Joueur::getInventaire(unsigned int i) const { 
        if (i > 5)
            throw SplendorException("Splendor::Joueur::getInventaire() : indice i invalide");
        return inventaire[i]; 
    }

    int Joueur::getBonus(unsigned int i) const { 
        if (i > 4)
            throw SplendorException("Splendor::Joueur::getBonus() : indice i invalide");
        return bonus[i]; 
    }

    /*
            =========================== SETTERS ===========================
    */

    bool Joueur::setInventaire(unsigned int i, unsigned int val){
        if(i > 5){
            throw SplendorException("Splendor::Joueur::setInventaire() : indice i invalide");
            return false;
        }
        inventaire[i] = val;
        return true;
    };  

    bool Joueur::setBonus(unsigned int i, unsigned int val){
        if(i > 4){
            throw SplendorException("Splendor::Joueur::setBonus() : indice i invalide");
            return false;
        }
        bonus[i] = val;
        return true;
    }; 

    /*
            =========================== FONCTIONS ==========================
    */


    bool Joueur::ajouterCarteReserve(const Carte &c){
        if (reserve.size() > 3){
            throw SplendorException("Splendor::Joueur::ajouterCarteReserve() : reserve pleine");
            return false;
        }
        reserve.push_back(&c);
        return true;
    };

    const Carte& Joueur::retirerCarteReserve(const Carte &c){
        if (reserve.empty())
            throw SplendorException("Splendor::Joueur::retirerCarteReserve() : reserve vide");
        
        vector<const Carte*>::iterator it = find(reserve.begin(), reserve.end(), &c);
        if(it == reserve.end()){
            throw SplendorException("Splendor::Pioche::piocher() : carte à supp inexistante");
        }
        reserve.erase(it);

        return c;
    };

    bool Joueur::addCartesRemportees(const Carte &c){
        cartesRemportees.push_back(&c);
        return 0;
    };

    void Joueur::addPDV(unsigned int i) {
        if (i<0){
            throw SplendorException("Splendor::Pioche::addPDV() : parametre i negatif");
        } 
        PDV += i; 
    }

    // AFFICHAGE

    void Joueur::afficherInventaire(std::ostream& f) const{
        f << "Inventaire: [";
        for (size_t i = 0; i < 5; i++) {
            f << inventaire[i] << ",";
        }
        f << inventaire[5] << "]" << std::endl;
    }

    void Joueur::afficherBonus(std::ostream& f) const{
        f << "Bonus: [";
        for (size_t i = 0; i < 4; i++) {
            f << bonus[i] << ",";
        }
        f << bonus[4] << "]" << std::endl;
    }

    void Joueur::afficherReserve() {
        for(auto i: getReserve() )
            i->afficherCarte();
    }   
    void Joueur::afficherCartesRemportees()  {
        for(auto i: getCartesRemportees() )
            i->afficherCarte();
    }

    /*
            =========================== ACTION DU JOUEUR ==========================
    */

    void Joueur::acheterCarte(const Carte& c, Plateau& p) {
        if (c.canBeBougth(*this)) {
            addCartesRemportees(c);
            //TODO: traitement sur l'inventaire du joueur
        }
        throw SplendorException("Splendor::Joueur::acheterCarte() : ressources insuffisantes");
    }

    void Joueur::prendreRessource(unsigned int i, Plateau& p) {
        if(i > 5 || i < 0)
            throw SplendorException("Splendor::Joueur::prendreRessource() : indice i invalide");
        if (!p.getBanque(i))
            throw SplendorException("Splendor::Joueur::prendreRessource() : Banque vide");
        p.setBanque(i, p.getBanque(i) - 1); //Retirer un jeton de la banque
        setInventaire(i, getInventaire(i) + 1); //Ajouter un jeton au joueur
    }

    void Joueur::selectCarte(const Carte& c, Plateau& p) {
        if (c.canBeBougth(*this))
            acheterCarte(c, p);
        ajouterCarteReserve(c); //Testdans ajouterCarteReserve de la taille de la réserve
    }
} 
