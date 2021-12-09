#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <array>
#include "jeu.h"
#include "../carte/carte.h"

namespace Splendor{

    Jeu& Jeu::getInstance(){
        if (handler.instance == nullptr)
            handler.instance = new Jeu;
        return *handler.instance;
    }

    void Jeu::freeInstance(){
        delete handler.instance;
        handler.instance = nullptr;
    }

    Jeu::Handler Jeu::handler = Handler();

Jeu::Jeu(){
    for (int i = 0; i<10; i++){
        int j = rand()%(11);
        ressources cst = {j,j,j,j,j};
        ressources bns = {j,j,j,j,j};
        
        cartes[Type::un].push_back(new CarteDeveloppement(cst, bns, Type::un, rand()%(8)));
    }

    for (int i = 0; i<10; i++){
        int j = rand()%(11);
        ressources cst = {j,j,j,j,j};
        ressources bns = {j,j,j,j,j};
        
        cartes[Type::deux].push_back(new CarteDeveloppement(cst, bns, Type::deux, rand()%(8)));
    }

    for (int i = 0; i<10; i++){
        int j = rand()%(11);
        ressources cst = {j,j,j,j,j};
        ressources bns = {j,j,j,j,j};
        
        cartes[Type::trois].push_back(new CarteDeveloppement(cst, bns, Type::trois, rand()%(8)));
    }

    for (int i = 0; i<10; i++){
        int j = rand()%(11);
        ressources cst = {j,j,j,j,j};
        ressources bns = {j,j,j,j,j};
        
        cartes[Type::nobles].push_back(new CarteNoble(cst, bns, rand()%(8)));
    }
}

}
