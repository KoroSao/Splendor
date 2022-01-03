#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#include "../carte/carte.h"
#include <map>
#include <array>

/**
* \file jeu.h
* Ce fichier permet de gérer un singleton responsable d'un jeu donné pour une partie
* \version 1.0
*/

using namespace std;


namespace Splendor{

void read_line_carteC_pdv(std::istringstream& line,Type type, ressources& couts, int& pdv);
void read_line_carteDev(std::istringstream& line,Type type,
                        ressources& couts,ressources& bonus, int& pdv);

string readFileIntoString(const string& path);

/**
* \class Jeu jeu.h
* Classe singleton responsable d'une partie donnée 
*/
class Jeu{
    protected:
        map<Type, vector<Carte*>> cartes;

        struct Handler{
            Jeu* instance;
            Handler() : instance(nullptr) {}
        };
        static Handler handler;

        Jeu();
        ~Jeu() = default;
        Jeu(const Jeu&) = delete;
        Jeu& operator=(const Jeu&) = delete;

    public:
        /**
       * \brief La fonction permet de créer une instance de jeu en vérifiant qu'il n'y en a pas déjà
       */
        static Jeu& getInstance();
        /**
       * \brief La fonction permet de supprimer la seule instance de jeu afin de pouvoir en créer une autre
       */
        static void freeInstance();
        /* //TODO: const*/vector<Carte*> getCartes(Type t){ return cartes[t]; }
        /**
       * \brief Permet de connaître le nombre de cartes d'un certain type
       * \param Type t Caractérise la carte (niveau 1, 2, 3 ou noble)
       * \return retournera le nombre d'éléments de cartes de type t
       */
        int getNbCartes(Type t){ return cartes[t].size(); }

};


}

#endif // JEU_H_INCLUDED
