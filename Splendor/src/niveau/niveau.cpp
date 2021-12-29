#include "niveau.h"

namespace Splendor{

    /*  ============================================================================
                                         CLASS NIVEAU
        ============================================================================ */
    Niveau::Niveau(int t, Type ty): pioche(ty), nb(0), nbMax(t), type(ty), cartes() {
        for (size_t i = 0; i < t; i++)
            piocherCarte();
    }





    const Carte& Niveau::retirerCarte(const Carte& c){
        if (cartes.empty())
            throw SplendorException("Splendor::Pioche::piocher() : niveau vide");

        vector<const Carte*>::iterator it = find(cartes.begin(), cartes.end(), &c);
        if(it == cartes.end()){
            throw SplendorException("Splendor::Pioche::piocher() : carte à supp inexistante");
        }
        cartes.erase(it);
        nb--;
        if(!getPioche().estVide()){
            piocherCarte();
        }
        return c;
    } 

    void Niveau::afficherNiveau(){
        for(auto i: getCartes()){
            i->afficherCarte();
        }
    }

    void Niveau::piocherCarte(){
        if (nb>=nbMax)
            throw SplendorException("Splendor::Pioche::piocher() : niveau plein");
        cartes.push_back(&pioche.piocher());
        nb++;
    }

}
