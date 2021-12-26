#include   "src/controleur/controleur.h"

using namespace Splendor;
int main(){
    try{
    Jeu::getInstance();
    for (Type t : {Type::nobles, Type::un, Type::deux, Type::trois}){
        for (Carte* carte : Jeu::getInstance().getCartes(t))
            carte->afficherCarte();
    }
    }
    catch(SplendorException& e){
        cout<< e.getInfo();
    }
    return 0;}
