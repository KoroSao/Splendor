#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include "../type/type.h"

/**
* \file carte.h
* Ce fichier permet de gérer les cartes
* \version 1.0
*/
using namespace std;

namespace Splendor{

    class Joueur;
    //pour alléger
    typedef array<int, 5> ressources;
    static map<int, std::string> ressources_name = {{0,"Emeraude"},{1, "Saphir"}, {2, "Rubis"}, {3, "Diamant"}, {4, "Onix"}};

    /**
    * \class Carte Carte.h
    * Classe abstraite
    */
    class Carte{
        private:
            const ressources couts;
        protected:
            Carte(ressources c):couts(c){}
        public:
            int getCouts(size_t i) const {return couts[i];}
            /**
           * \brief Jeu est le seul constructeur de la classe Carte
           */
            friend class Jeu;
            /**
           * \brief Permet de savoir si une carte peut être achetée
           * \param Joueur& j Prend le joueur qui souhaite acheter une carte en paramètre
           * \return retournera vrai si le joueur peut acheter dans les class où la méthode a été redéfinie
           */
            virtual bool canBeBougth(Joueur& j) const = 0;
            /**
           * \brief Permet d'afficher une carte dans les classes où cette méthode a été redéfinie
           */
            virtual void afficherCarte(std::ostream& f = std::cout) const =  0;
    };

    /**
    * \class Carte_avec_bonus  Carte.h
    * Classe abstraite qui hérite de carte
    */
    class Carte_avec_bonus : public Carte{
        private:
            const ressources bonus;
        protected:
            Carte_avec_bonus(ressources c, ressources b) : Carte(c), bonus(b) {};
        public:
            /**
           * \brief Permet de connaître le bonus associé à une carte
           * \param size_t i Prend en paramètre la catégorie de pierre
           * \return le bonus associé à la pierre n°i
           */
            int getBonus(size_t i) const { return bonus[i]; }
            void afficherCarte(std::ostream& f = std::cout) const override {}
    };

    /**
    * \class Carte_avec_bonus  Carte.h
    * Classe : carte de développement qui contiennent un bonus
    */
    class CarteDeveloppement : public Carte_avec_bonus{
        friend class Jeu;
        private:
            const int PDV;
            const Type type;
            CarteDeveloppement(ressources c, ressources b, Type t,  int pdv): Carte_avec_bonus(c, b), type(t), PDV(pdv) {};
        public:
            /**
           * \brief Permet d'avoir le niveau de la carte
           */
            const Type getType() const { return type; }
            /**
           * \brief Permet d'avoir le nombre de points de victoire de la carte
           */
            const int getPDV() const { return PDV; }
            bool canBeBougth(Joueur& j) const override;
            void afficherCarte(std::ostream& f = std::cout) const override;
    };

    /**
    * \class CarteNoble Carte.h
    * Classe des cartes nobles, hérite de Carte
    */
    class CarteNoble : public Carte{
        friend class Jeu;
        private:
            const int PDV;
            CarteNoble(ressources c, int pdv):Carte(c), PDV(pdv){};
        public:
            /* //TODO:: à remettre en privé un jour*/
            /**
           * \brief Permet d'avoir le nombre de points de victoire de la carte
           */
            const int getPDV() const {return PDV;};
            bool canBeBougth(Joueur& j) const override;
            void afficherCarte(std::ostream& f = std::cout) const override;
    };

    /**
    * \class CarteCite Carte.h
    * Classe des cartes nobles, hérite de Carte
    */
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
