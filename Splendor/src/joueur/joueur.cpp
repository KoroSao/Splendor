#include "joueur.h"

namespace Splendor {

    /*
            =========================== GETTERS ===========================
    */
    unsigned int Joueur::getInventaire(unsigned int i) const {
        if (i > 5)
            throw SplendorException("Splendor::Joueur::getInventaire() : indice i invalide");
        return inventaire[i]; 
    }

    unsigned int Joueur::getBonus(unsigned int i) const {
        if (i > 4)
            throw SplendorException("Splendor::Joueur::getBonus() : indice i invalide");
        return bonus[i]; 
    }

    unsigned int Joueur::getJetonsPris(unsigned int i) {
        if (i > 4)
            throw SplendorException("Splendor::Joueur::getJetonsPris() : indice i invalide");
        return jetonsPris[i]; 
    }

    /*
            =========================== SETTERS ===========================
    */

    void Joueur::setInventaire(unsigned int i, unsigned int val){
        if(i > 5){
            throw SplendorException("Splendor::Joueur::setInventaire() : indice i invalide");
        }
        inventaire[i] = val;
    };  

    void Joueur::setBonus(unsigned int i, unsigned int val){
        if(i > 4){
            throw SplendorException("Splendor::Joueur::setBonus() : indice i invalide");
        }
        bonus[i] = val;
    };

    void Joueur::setJetonsPris(unsigned int i, unsigned int val){
        if(i > 4)
            throw SplendorException("Splendor::Joueur::setJetonsPris() : indice i invalide");
        jetonsPris[i] = val;
    }


    /*
            =========================== FONCTIONS ==========================
    */


    void Joueur::ajouterCarteReserve(const Carte &c){
        if (reserve.size() > 3){
            throw SplendorException("Splendor::Joueur::ajouterCarteReserve() : reserve pleine");
        }
        reserve.push_back(&c);
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

    void Joueur::addCartesRemportees(const Carte &c){
        cartesRemportees.push_back(&c);
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

    // -----------Controle de tours-------

     bool Joueur::inventaireFull() const{
        //Retourne vrai si l'inventaire du joueur est plein (faux sinon)
        unsigned int nbJetons = 0;

        for (size_t i = 0; i < 5; i++)
            nbJetons += getInventaire(i);

        return nbJetons>10;
    }

    
} 
