#include "carte.h"
#include <iostream>

using namespace std;

namespace Splendor{

bool CarteDeveloppement::canBeBougth(Joueur &j){
    /*Pour pouvoir acheter un carte le joueur doit avoir les ressources
    et les bonus suffisant, et si il en manque il doit pouvoir compenser avec des jokers*/
    int jetons_manquants = 0;
    for (size_t i = 0; i<5;i++) jetons_manquants += max(0, getCouts(i)-j.getBonus(i)-j.getInventaire(i));
    return j.getInventaire(5)>jetons_manquants;
}

bool CarteNoble::canBeBougth(Joueur &j){
    /*Pour acquérir un carte noble il suffit d'avoir les bonus requis*/
    int bonus_manquants = 0;
    for (size_t i = 0; i<5;i++) bonus_manquants += max(0, getCouts(i)-j.getBonus(i));
    return bonus_manquants==0;
}

bool CarteCite::canBeBougth(Joueur &j){
    /*Pour acquérir un carte cite il faut les bonus requis
    et les points de victoire (points de prestige) requis*/
    int bonus_manquants = 0;
    for (size_t i = 0; i<5;i++) bonus_manquants += max(0, getCouts(i)-j.getBonus(i));
    return bonus_manquants==0 && j.getPV() >= pdv_requis;
}

}
