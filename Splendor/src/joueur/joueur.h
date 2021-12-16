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
            unsigned int id;                    //const
            string nom;                         //
            int inventaire[6];                  // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            int bonus[5];                       // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            vector<const Carte*> reserve;             // reserve (un joueur peut posséder au max 3 cartes en réserve)
            //unsigned int nbCartesReservee;      //Potentiellement inutile avec reserve.size()
            vector<const Carte*> cartesRemportees;    //Stocke les cartes gagnées par le joueur (size infinie)
            unsigned int PDV;                    // Nombre de point de victoire du joueur

        public:
            // ----------- Constructor et Destructor -----------
            Joueur(unsigned int id, const string& nom) : 
                id(id), nom(nom), inventaire(), bonus(),    //Par défaut les tableaux sont initaliés à 0
                reserve(), cartesRemportees(), PDV(0) {};
            
            ~Joueur() = default;


            //----------- Getters -----------
            unsigned int getId() const { return id; }
            const string getNom() const { return nom; }

            int getInventaire(unsigned int i) const;
            int* getInventaire() { return inventaire; }

            int getBonus(unsigned int i) const;
            int* getBonus() { return bonus; }


            vector<const Carte*> getReserve() { return reserve; }

            vector<const Carte*> getCartesRemportees() { return cartesRemportees; }

            unsigned int getPDV() const { return PDV; }


            // ----------- Setters -----------
                //pas besoin de setters pour l'id et le nom car fait à la création
                //TODO: voir l'utilité du bool ou du void
            bool setInventaire(unsigned int i, unsigned int val);        
            bool setBonus(unsigned int i, unsigned int val); 

            bool addCartesRemportees(const Carte &c);

            bool ajouterCarteReserve(const Carte &c);
            const Carte& retirerCarteReserve(const Carte &c);
        
            void addPDV(unsigned int i);

            // ----------- Affichage -----------
            void afficherInventaire(std::ostream& f = std::cout) const;
            void afficherBonus(std::ostream& f = std::cout) const;
            void afficherReserve() ;
            void afficherCartesRemportees();

            // ------------ Action du joueur --------------
            void acheterCarte(const Carte& c, Plateau& p);
            void prendreRessource(unsigned int i, Plateau& p);
            void selectCarte(const Carte&c, Plateau &p);


    };

} 

#endif