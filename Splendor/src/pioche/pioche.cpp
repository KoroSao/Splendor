#include "pioche.h"

#include <sys/types.h>
#include <unistd.h>

using namespace std;

namespace Splendor {

  //en ayant les méthodes dans jeu
  Pioche::Pioche(Type t) :
    cartes(Jeu::getInstance().getCartes(t)), nb(Jeu::getInstance().getNbCartes(t)), type(t) {
      unsigned int compteur = 0;
      srand(time(NULL));
  }

   Carte& Pioche::piocher() {
    if (estVide())
      throw SplendorException("Pioche vide");

    size_t x = rand() % nb; //on choisit une carte au hasard
    Carte* c = cartes[x]; //on retient l'adresse de la carte
    //std::cout << cartes.begin() << std::endl;
    vector<Carte*>::iterator it = find(cartes.begin(), cartes.end(), c);
    if(it == cartes.end()){
      throw SplendorException("Splendor::Pioche::piocher() : carte à supp inexistante");
    }
    cartes.erase(it);
    nb--;
    return *c;
  }

}
