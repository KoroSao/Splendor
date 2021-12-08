#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include <vector>
#include <iostream>
#include <array>
#include "../joueur/joueur.h"

using namespace std;


namespace Splendor
{
//Fake class
class Joueur{
    public:
    int getInventaire(size_t i){return 0;};
    int getBonus(size_t i){return 0;};
    int getPV(){return 0;};
};

//Definition de l'enum type pour la classe Jeu et CarteDevelopement
enum class Type {nobles, cite, un=1, deux=2, trois=3 };

//pour all�ger
typedef array<int, 5> ressources;

//classe abstraite
class Carte{
    const ressources couts;
protected:
    Carte(ressources c):couts(c){};
public:
    const int getCouts(size_t i){return couts[i];};
    virtual bool canBeBougth(Joueur& joueur);
    friend class Jeu;//Jeu est le seul constructeur de la classe Carte
};

//classe abstraite
class Carte_avec_bonus : public Carte{
    const ressources bonus;
protected:
    Carte_avec_bonus(ressources c, ressources b):Carte(c),bonus(b){};
public:
    const int getBonus(size_t i){return bonus[i];};
};


class CarteDeveloppement : public Carte_avec_bonus{
    const int PDV;
    const Type type;
    CarteDeveloppement(ressources c, ressources b,Type t,  int pdv):
        Carte_avec_bonus(c, b), type(t), PDV(pdv){};
public:
    const Type getType(){return type;};
    const int getPDV(){return PDV;};
    bool canBeBougth(Joueur& joeur) override;
};

class CarteNoble : public Carte_avec_bonus{
    const int PDV;
    CarteNoble(ressources c,ressources b, int pdv):Carte_avec_bonus(c, b), PDV(pdv){};
public:
    const int getPDV(){return PDV;};
    bool canBeBougth(Joueur& joeur) override;
};

class CarteCite : public Carte{
    const int pdv_requis;
    CarteCite(ressources c, int pdv_r):Carte(c), pdv_requis(pdv_r){};
public:
    bool canBeBougth(Joueur& joueur) override;
};

}

#endif // CARTE_H_INCLUDED