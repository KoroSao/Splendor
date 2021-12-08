#include "pioche.h"

using namespace std;
namespace Splendor {




    //en ayant les méthodes dans jeu
Pioche::Pioche(Type t) : cartes(Jeu::getInstance().getNbCartesType()), //vecteur
                    nb(Jeu::getInstance().getNbCartesType()), type (t) {
    unsigned int compteur =0;
    srand(time(NULL));
    for (auto carte:Jeu::getInstance().getCartesType(t)){
      cartes[compteur]=&carte;
      compteur++;
    }
}

const Carte& Pioche::piocher() {
  if (estVide())
   throw SetException("Pioche vide");
  size_t x = rand() % nb; //on choisit une carte au hasard
  const Carte* c = cartes[x]; //on retient l'adresse de la carte
  cartes.erase(cartes.begin()+(x-1));
  nb--;
  return *c;
}

}
int main(){return 0;}
