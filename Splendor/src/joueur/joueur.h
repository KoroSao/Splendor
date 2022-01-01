#ifndef _JOUEUR_H
#define _JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <algorithm>

#include "../carte/carte.h"
#include "../plateau/plateau.h"
#include "../splendorException/splendorexception.h"

using namespace std;

/**
* \file joueur.h
* Ce fichier permet de gérer tout le contexte d'un joueur (ses cartes, son iventaire,...)
* \version 1.0
*/

namespace Splendor{
    // ----------- Début de la classe Joueur : -----------

    /**
    * \class Joueur joueur.h
    * La classe gère tout les attributs associés à un joueur ainsi que l'accès, l'affichage et les modofications
    */
    class Joueur {
        private:
            unsigned int id;
            string nom;
            /**
           * \brief ordre : émeraude / saphir / rubis / diamant / onyx / joker
           */
            unsigned int inventaire[6];
            /**
            * \brief   ordre : émeraude / saphir / rubis / diamant / onyx / joker
            */
            unsigned int bonus[5];
            /**
            * \brief Stocke les jetons pris à la fin de son tour
            */
            unsigned int jetonsPris[5];
            /**
            * \brief reserve (un joueur peut posséder au max 3 cartes en réserve)
            */
            vector<const Carte*> reserve;
            /**
            * \brief Stocke les cartes gagnées par le joueur (size infinie)
            */
            vector<const Carte*> cartesRemportees;
            /**
            * \brief Nombre de point de victoire du joueur
            */
            unsigned int PDV;

        public:
            friend class Controleur;
            // ----------- Constructor et Destructor -----------
            /**
            * \brief Par défaut les tableaux sont initaliés à 0
            */
            Joueur(unsigned int id, const string& nom) :
                id(id), nom(nom), inventaire(), bonus(), jetonsPris(),
                reserve(), cartesRemportees(), PDV(0) {};

            ~Joueur() = default;

            //----------- Getters -----------
            /**
            * \return Renvoie l'id d'un joueur
            */
            unsigned int getId() const { return id; }
            /**
            * \return Renvoie le nom d'un joueur
            */
            const string getNom() const { return nom; }
            /**
            * \brief Donne accès à la ième catégorie de l'inventaire d'un joueur
            */
            unsigned int getInventaire(unsigned int i) const;
            /**
            * \return Renvoie un pointeur sur la première case du tableau de l'inventaire d'un joueur
            */
            unsigned int* getInventaire() { return inventaire; }
            /**
            * \brief Donne le nombre de bonus de la ième catégorie détenu par le joueur
            */
            unsigned int getBonus(unsigned int i) const;
            /**
            * \return Renvoie un pointeur sur la première case du tableau des bonus d'un joueur
            */
            unsigned int* getBonus() { return bonus; }
            /**
            * \return Retourne le nombre de jetons de la ième catégorie qui ont été pris
            */
            unsigned int getJetonsPris(unsigned int i);
            /**
            * \return retourne un vecteur comprenant des pointeurs sur les cartes réservées par un joueur
            */
            vector<const Carte*> getReserve() { return reserve; }
            /**
            * \return retourne un vecteur comprenant des pointeurs sur les cartes gagnées par un joueur
            */
            vector<const Carte*> getCartesRemportees() { return cartesRemportees; }
            /**
            * \return retourne le nombre de points de victoire d'un joueur
            */
            unsigned int getPDV() const { return PDV; }

            // ----------- Setters -----------
            /**
            * \brief Permet de modifier par val le nombre de la ième catégorie de l'inventaire
            */
            void setInventaire(unsigned int i, unsigned int val);
            /**
            * \brief Permet de modifier par val le nombre de la ième catégorie du tableau de bonus
            */
            void setBonus(unsigned int i, unsigned int val);
            /**
            * \brief Permet de prendre val jetons de la ième catégorie
            */
            void setJetonsPris(unsigned int i, unsigned int val);
            /**
            * \brief Permet d'ajouter une nouvelle carte (celle qui a été remportée) dans cartesRemportees
            */
            void addCartesRemportees(const Carte &c);
            /**
            * \brief Permet d'ajouter une nouvelle carte dans la reserve à condition qu'elle ne soit pas pleine (<3)
            */
            void ajouterCarteReserve(const Carte &c);
            /**
            * \brief Permet de retirer une carte de la reserve
            */
            void retirerCarteReserve(const Carte &c);
            /**
            * \brief Permet d'ajouter la valeur i au nombre de PDV du joueur
            */
            void addPDV(unsigned int i);

            // ----------- Affichage -----------
            /**
            * \brief Permet d'afficher l'inventaire du joueur
            */
            void afficherInventaire(std::ostream& f = std::cout) const;
            /**
            * \brief Permet d'afficher le nombre de bonus dans chaque catégorie du joueur
            */
            void afficherBonus(std::ostream& f = std::cout) const;
            /**
            * \brief Permet d'afficher le contenu de la reserve d'un joueur
            */
            void afficherReserve() ;
            /**
            * \brief Permet d'afficher les cartes qu'un joueur a remportées
            */
            void afficherCartesRemportees();

            // -----------Controle de tours-------
            /**
            * \return Retourne vrai si l'inventaire du joueur est plein (faux sinon)
            */
            bool inventaireFull() const;
            /**
            * \return Retourne vrai si le joueur peut prétendre à la victoire, si son nombre de point de victoire est > à 15 (faux sinon)
            */
            bool hasVictoryCondition() const { return getPDV() >= 15; }



    };

}

#endif
