#include "carte.h"
#include "../joueur/joueur.h"

using namespace std;

namespace Splendor{


    bool CarteDeveloppement::canBeBougth(Joueur &j) const {
        /*Pour pouvoir acheter un carte le joueur doit avoir les ressources
        et les bonus suffisant, et si il en manque il doit pouvoir compenser avec des jokers*/
        unsigned int jetons_manquants = 0;
        for (size_t i = 0; i<5;i++)
            jetons_manquants += max((unsigned int)0, getCouts(i)-j.getBonus(i)-j.getInventaire(i));
        return j.getInventaire(5)>=jetons_manquants;
    }

    bool CarteNoble::canBeBougth(Joueur &j) const {
        /*Pour acquérir un carte noble il suffit d'avoir les bonus requis*/
        unsigned int bonus_manquants = 0;
        for (size_t i = 0; i<5;i++)
            bonus_manquants += max((unsigned int)0, getCouts(i)-j.getBonus(i));
        return bonus_manquants==0;
    }

    bool CarteCite::canBeBougth(Joueur &j)const {
        /*Pour acquérir un carte cite il faut les bonus requis
        et les points de victoire (points de prestige) requis*/
        unsigned int bonus_manquants = 0;
        for (size_t i = 0; i<5;i++)
            bonus_manquants += max((unsigned int)0, getCouts(i)-j.getBonus(i));
        return bonus_manquants==0 && (int)j.getPDV() >= pdv_requis;
    }

    void CarteDeveloppement::afficherCarte(std::ostream& f) const {
        f << "Carte Developement, Niveau"<< toString(getType())<<std::endl;
        f << "PDV : " << getPDV() << std::endl;
        f << "cout : " << getCouts(0) << " " << getCouts(1) << " " << getCouts(2) << " " << getCouts(3) << " " << getCouts(4) << std::endl;
        f << "bonus : " << getBonus(0) << " " << getBonus(1) << " " << getBonus(2) << " " << getBonus(3) << " " << getBonus(4) << std::endl;
        f << " - - -" << std::endl;
    }

    void CarteNoble::afficherCarte(std::ostream& f) const {
        f << "Type: Noble"<< std::endl;
        f << "PDV : " << getPDV() << std::endl;
        f << "cout : " << getCouts(0) << " " << getCouts(1) << " " << getCouts(2) << " " << getCouts(3) << " " << getCouts(4) << std::endl;
        f << " - - -" << std::endl;
    }


}
