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

#include "../type/type.h"
#include "../carte/carte.h"
#include "../jeu/jeu.h"

#include "../splendorException/splendorexception.h"

using namespace std;

namespace Splendor {



class Pioche {
    vector<const Carte*> cartes;
    size_t nb = 0 ;
    Type type ;
public :
    Pioche(Type t);
    ~Pioche(); //se fait auto car vecteur
    size_t getNbCartes() const { return nb; }
    Type getType() const { return type; }
    bool estVide() const { return (nb==0); }
    const Carte& piocher();
};
}

#endif
