#ifndef _NIVEAU_H
#define _NIVEAU_H

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
class Pioche {};

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



class Niveau {
    vector<Carte*> cartes;
    Pioche& pioche;
    Type type ;
    unsigned int taille;
public :
    Niveau(Type t);
    ~Niveau();
    Carte ::Carte getCartes();
    Carte ::Carte* retirerCarte(int i);
    Carte ::Carte* getCarteFromPioche();
};
}

#endif
