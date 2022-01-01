#ifndef _PIOCHE_H
#define _PIOCHE_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <array>
#include <cstdlib>
#include <map>
#include <vector>
#include <time.h>
#include <algorithm>

#include "../type/type.h"
#include "../carte/carte.h"
#include "../jeu/jeu.h"

#include "../splendorException/splendorexception.h"

using namespace std;
/**
* \file pioche.h
* Ce fichier permet de gérer les pioches
* \version 1.0
*/

namespace Splendor {

/**
* \class Pioche pioche.h
* Classe qui permet de se renseigner sur une pioche spécifique
*/
class Pioche {
    vector<Carte*> cartes;
    size_t nb = 0;
    Type type;
public :
    Pioche(Type t);
    ~Pioche() = default;
    /**
   * \return Cette fonction renvoie le nombre de carte de la pioche
   */
    size_t getNbCartes() const { return nb; }
    /**
   * \return Cette fonction renvoie le type de carte de la pioche
   */
    Type getType() const { return type; }
    /**
   * \return Cette fonction renvoie true si la pioche est vide et false sinon
   */
    bool estVide() const { return (nb==0); }
    /**
   * \brief Cette fonction permet de piocher une carte aléatoirement dans la pioche 
   */
    Carte& piocher();
};
}

#endif
