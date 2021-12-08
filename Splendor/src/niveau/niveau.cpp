#include "niveau.h"

namespace Splendor{

    /*  ============================================================================
                                         CLASS NIVEAU
        ============================================================================ */
    Niveau::Niveau(int t, Type ty): pioche(ty), nb(0), nbMax(t), type(ty), cartes() {
      for (size_t i = 0; i < 3; i++){
        ajouterCarte(pioche.piocher());
      }
    }; //{nullptr, nullptr, nullptr, nullptr}


    void Niveau::ajouterCarte(const Carte& c){
        if (nb>=nbMax)
            SplendorException("Niveau plein");
        
        //Carte *newc = new Carte c;   
        cartes.push_back(c);
        //cartes[Type::un].push_back(new CarteDeveloppement(cst, bns, Type::un, i));
    }


    const Carte& Niveau::retirerCarte(const Carte& c){
        size_t i = 0;
        //Décalage sur la bonne carte
        while (i < nb && cartes[i] != &c)
            i++;
        if (i == nb) //Arrivé à la fin du paquet sans trouver la carte
            throw SplendorException("Carte inexistante");
        i++;
        //Redécalage des cartes au début du tableau
        while (i < nb - 1){
            cartes[i] = cartes[i+1];
            i++;
        }
        nb--;
        return c;
    } 

}