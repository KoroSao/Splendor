#include "controleur.h"

namespace Splendor{

    Controleur& Controleur::getInstance(){
        if (handler.instance == nullptr)
            handler.instance = new Controleur;
        return *handler.instance;
    }

    void Controleur::freeInstance(){
        delete handler.instance;
        handler.instance = nullptr;
    }

    Controleur::Handler Controleur::handler = Handler();

}