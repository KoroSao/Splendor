#include "joueur.h"

namespace Splendor {

    bool Joueur::setInventaire(unsigned int i, unsigned int val){
        if(i > 5)
            SplendorException("class Joueur : setInventaire() -> indice i invalide");
        inventaire[i] = val;
        return 0;
    };  

    bool Joueur::setBonus(unsigned int i, unsigned int val){
        if(i > 5)
            throw SplendorException("class Joueur : setBonus() -> indice i invalide");
        bonus[i] = val;
        return 0;
    };  
    
    bool Joueur::addCarteReserve(const Carte &c){
        if (nbCartesReservee > 2)
            throw SplendorException("class Joueur : setReserve() -> reserve pleine");
        reserve[nbCartesReservee++] = &c;
    };

    bool Joueur::removeCarteReserve(const Carte &c){
        unsigned int i = 0;
        //Décalage sur la bonne carte
        while (i < nbCartesReservee && reserve[i] != &c)
            i++;
        if (i == nbCartesReservee) //Arrivé à la fin de la réserve sans trouver la carte
            throw SplendorException("class Joueur : remvoveCarteReserve() -> carte inexistante");
        i++;
        //Redécalage des cartes au début du tableau
        while (i < nbCartesReservee - 1){
            reserve[i] = reserve[i+1];
            i++;
        }
        nbCartesReservee--;
        //L'execution s'est bien passé, en retourne 0
        return 0;
    };

    bool Joueur::addCartesRemportees(const Carte &c){
        CartesRemportees[nbCartesRemportees++] = &c;
        return 0;
    };


} 
