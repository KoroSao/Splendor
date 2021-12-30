#include "niveau.h"

namespace Splendor{

    /*  ============================================================================
                                         CLASS NIVEAU
        ============================================================================ */
    Niveau::Niveau(int t, Type ty): pioche(ty), nb(0), nbMax(t), type(ty), cartes() {
        for (size_t i = 0; i < t; i++)
            piocherCarte();
    }


    bool  Niveau::possedeCarte(const Carte& c) {
        vector<const Carte*>::iterator it = find(cartes.begin(), cartes.end(), &c);
        return (it != cartes.end());
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

        //Détour pour ne pas repiocher quand carte noble
        const CarteNoble* cn = dynamic_cast<const CarteNoble*>(&c);
        if(!getPioche().estVide() && !cn){
            piocherCarte();
        } else {
            std::cout << "C'est une carte Noble qu'on veut delete donc pas de rajout" << std::endl;
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
