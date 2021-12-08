#include <iostream>

//#include "../src/controleur/controleur.h"
#include "../src/carte/carte.h"
#include "../src/jeu/jeu.h"

using namespace Splendor;

int main(){
    std::cout << "Hello World !" << std::endl;

    array<int, 5> cArray = {3, 4, 5, 3, 1};
    array<int, 5> bArray = {0, 0, 0, 1, 0};
    CarteDeveloppement c(cArray, bArray, Type::un, 4);

    std::cout << "c : " << c.getPDV() << std::endl;

    std::cout << Jeu::getInstance().getNbCartes(Type::un) << std::endl;

    Jeu::getInstance().getCartes(Type::un)[0]->getCouts(4);

    return 0;
}


//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/controleur/controleur.cpp ../src/jeu/jeu.cpp ../src/joueur/joueur.cpp ../src/niveau/niveau.cpp ../src/plateau/plateau.cpp ../src/type/type.cpp -o main && ./main

//g++ -std=c++11 main.cpp ../src/carte/carte.cpp ../src/jeu/jeu.cpp ../src/type/type.cpp -o main && ./main