#ifndef _JOUEUR_H
#define _JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

namespace Splendor {
    
    //Exception class for the game Splendor
    class SplendorException {
        private:
            string info;
        public:
            SplendorException(const string & i): info(i) {}
            string getInfo() const { return info; }
    };

    //Fake class
    class Carte{
        public:
            Carte()=default;
    };

    // ----------- Début de la classe Joueur : -----------

    class Joueur {
        private:
            unsigned int id;                    //
            string nom;                         //
            int inventaire[6];                  // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            int bonus[6];                       // ordre : émeraude / saphir / rubis / diamant / onyx / joker
            Carte reserve[3];                   //
            unsigned int nbCartesReservee;      //
            Carte **CartesRemportees;           //
            unsigned int nbCartesRemportees;    // 
            unsigned int PV;                    // Nombre de point de victoire du joueur

        public:
            // ----------- Constructor et Destructor -----------
            Joueur(unsigned int id, const string& nom) : 
                id(id), nom(nom), inventaire({0,0,0,0,0,0}), bonus({0,0,0,0,0,0}), reserve(), nbCartesReservee(0), CartesRemportees(), nbCartesRemportees(0), PV(0) {};
            
            ~Joueur() { delete[] CartesRemportees; }


            //----------- Getters -----------
            unsigned int getId() const { return id; }
            const string getNom() const { return nom; }

            int getInventaire(unsigned int i) const { return inventaire[i]; }
            //const int* getInventaire() const { return inventaire; }

            int getBonus(unsigned int i) const { return bonus[i]; }
            //const int* getBonus() const { return bonus; }

            const Carte* getReserve() const { return reserve; }
            unsigned int getNbCartesReservee() const { return nbCartesReservee; }

            const Carte** getCartesRemportees() { return CartesRemportees; }
            unsigned int getNbCartesRemportees() const { return nbCartesRemportees; }

            unsigned int getPV() const { return PV; }


            // ----------- Setters -----------
                //pas besoin de setters pour l'id et le nom car fait à la création
            bool setInventaire(unsigned int i, unsigned int val);        
            bool setBonus(unsigned int i, unsigned int val); 

            bool addCarteReserve(const Carte &c);
            bool removeCarteReserve(const Carte &c);
            
            bool addCartesRemportees(const Carte &c);

            void addPV(unsigned int i) { PV += i; }


            // ----------- Fonctions d'usage -----------
            void reserverCarte(const Carte&);
            void acheterCarte();
    };

} 

#endif