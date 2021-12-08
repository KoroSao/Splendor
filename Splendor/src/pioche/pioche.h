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

using namespace std;

namespace Splendor {

enum class Type { Nobles, cite, un=1, deux=2, trois=3 };

class Carte {}; //juste pour eviter erreur de compil

class SetException : public exception {
public:
    SetException (const string& info);
};

class Jeu {
    map<Type,vector<Carte>> cartes;
public:
    vector<Carte> getCartesType(Type t){return cartes[t];};
    static Jeu& getInstance();
    size_t getNbCartesType();
}; //juste pour eviter erreur de compil

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
