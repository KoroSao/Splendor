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
        ressources cst = {i,i*3,i,10-i,i*5};
        ressources bns = {10-i,10-i,i,i*2,i};
        
        cartes[Type::un].push_back(new CarteDeveloppement(cst, bns, Type::un, i));
    }
}

}
