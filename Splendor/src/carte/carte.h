#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include "../type/type.h"



using namespace std;

namespace Splendor{

    class Joueur;
    //pour alléger
    typedef array<unsigned int, 5> ressources;
    static map<int, std::string> ressources_name = {{0,"Emeraude"},{1, "Saphir"}, {2, "Rubis"}, {3, "Diamant"}, {4, "Onix"}};
    //classe abstraite
    class Carte{
        private:
            const ressources couts;
        protected:
            Carte(ressources c):couts(c){}
        public:
            unsigned int getCouts(size_t i) const {return couts[i];}
            friend class Jeu; //Jeu est le seul constructeur de la classe Carte
            virtual bool canBeBougth(Joueur& j) const = 0;
            virtual void afficherCarte(std::ostream& f = std::cout) const =  0;
    };

    //classe abstraite
    class Carte_avec_bonus : public Carte{
        private:
            const ressources bonus;
        protected:
            Carte_avec_bonus(ressources c, ressources b) : Carte(c), bonus(b) {};
        public:
            int getBonus(size_t i) const { return bonus[i]; }
            void afficherCarte(std::ostream& f = std::cout) const override {}
    };


    class CarteDeveloppement : public Carte_avec_bonus{
        friend class Jeu;
        private:
            const int PDV;
            const Type type;
            CarteDeveloppement(ressources c, ressources b, Type t,  int pdv): Carte_avec_bonus(c, b), type(t), PDV(pdv) {};
        public:
            const Type getType() const { return type; }
            const int getPDV() const { return PDV; }
            bool canBeBougth(Joueur& j) const override;
            void afficherCarte(std::ostream& f = std::cout) const override;
    };

    class CarteNoble : public Carte{
        friend class Jeu;
        private:
            const int PDV;
            CarteNoble(ressources c, int pdv):Carte(c), PDV(pdv){};
        public:
            /* //TODO:: à remettre en privé un jour*/

            const int getPDV() const {return PDV;};
            bool canBeBougth(Joueur& j) const override;
            void afficherCarte(std::ostream& f = std::cout) const override;
    };

    class CarteCite : public Carte{
        friend class Jeu;
        private:
            const int pdv_requis;
            CarteCite(ressources c, int pdv_r): Carte(c), pdv_requis(pdv_r){};
        public:
            bool canBeBougth(Joueur& j) const override;
            void afficherCarte(std::ostream& f = std::cout) const override {}
    };

}

#endif // CARTE_H_INCLUDED
