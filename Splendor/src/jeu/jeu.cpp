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
    for (size_t i =0; i<10; i++){    
        ressources cst = {1,2,3,4,5};
        ressources bns = {5,4,3,2,1};
        CarteDeveloppement c(cst, bns, Type::un, i);
        cartes[Type::un].push_back(&c);
    }
}

}
