#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "carte.h"
#include <map>
#include <array>

using namespace std;

namespace Splendor{


class Jeu{
protected:
    map<Type, vector<Splendor::Carte*>> cartes;
public:
    vector<Carte*> getCartes(Type t){return cartes[t];};
};

class Jeu_Classique:public Jeu{
    Jeu_Classique();
};

class Jeu_Cite:public Jeu{
    Jeu_Cite();
};

}

#endif // JEU_H_INCLUDED
