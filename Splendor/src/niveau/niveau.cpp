#include "niveau.h"

using namespace std;
namespace Splendor {

    //en ayant les méthodes dans jeu
Niveau::Niveau(Type t) : cartes(Jeu::getInstance().getNbCartesType()), //vecteur
                    pioche (), type (t), taille(4) {
    unsigned int compteur =0;
    srand(time(NULL));
    for (auto carte:Jeu::getInstance().getCartesType(t)){
      cartes[compteur]=&carte;
      compteur++;
    }
}

}

