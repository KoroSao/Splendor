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

namespace Splendor{
    // ----------- Début de la classe Joueur : -----------

    class Joueur {
        private:
            unsigned int id;                            
            string nom;                                 
            unsigned int inventaire[6];                          // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            unsigned int bonus[5];                               // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            unsigned int jetonsPris[5];                          //Stocke les jetons prix à la fin de son tour
            vector<const Carte*> reserve;               // reserve (un joueur peut posséder au max 3 cartes en réserve)
            vector<const Carte*> cartesRemportees;      //Stocke les cartes gagnées par le joueur (size infinie)
            unsigned int PDV;                          // Nombre de point de victoire du joueur

        public:
            friend class Controleur;
            // ----------- Constructor et Destructor -----------
            Joueur(unsigned int id, const string& nom) : 
                id(id), nom(nom), inventaire(), bonus(), jetonsPris(),   //Par défaut les tableaux sont initaliés à 0
                reserve(), cartesRemportees(), PDV(0) {};
            
            ~Joueur() = default;

            //----------- Getters -----------
            unsigned int getId() const { return id; }
            const string getNom() const { return nom; }
            unsigned int getInventaire(unsigned int i) const;
            unsigned int* getInventaire() { return inventaire; }
            unsigned int getBonus(unsigned int i) const;
            unsigned int* getBonus() { return bonus; }
            unsigned int getJetonsPris(unsigned int i);
            vector<const Carte*> getReserve() { return reserve; }
            vector<const Carte*> getCartesRemportees() { return cartesRemportees; }
            unsigned int getPDV() const { return PDV; }

            // ----------- Setters -----------
            void setInventaire(unsigned int i, unsigned int val);        
            void setBonus(unsigned int i, unsigned int val); 
            void setJetonsPris(unsigned int i, unsigned int val);
            void addCartesRemportees(const Carte &c);
            void ajouterCarteReserve(const Carte &c);
            void retirerCarteReserve(const Carte &c);
            void addPDV(unsigned int i);

            // ----------- Affichage -----------
            void afficherInventaire(std::ostream& f = std::cout) const;
            void afficherBonus(std::ostream& f = std::cout) const;
            void afficherReserve() ;
            void afficherCartesRemportees();

            // -----------Controle de tours-------
            bool inventaireFull() const;
            bool hasVictoryCondition() const { return getPDV() >= 15; }
            


    };

} 

#endif
