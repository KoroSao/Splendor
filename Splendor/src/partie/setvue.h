#ifndef SETVUE_H
#define SETVUE_H

#include <iostream>
#include <map>
#include <vector>
#include "../controleur/controleur.h"
#include <QPushButton>
#include "vueCarte.h"
#include "vuepioche.h"

class SetVue
{
    vector<VueCarte*> vueCarteDevI;
    vector<VueCarte*> vueCarteDevII;
    vector<VueCarte*> vueCarteDevIII;
    vector<VueCarte*> vueCarteNobles;
    vector<VueCarte*> vueCarteReserve;
    vector<VuePioche*> vuePioche;
public:
    SetVue(int);
    //getter
    vector<QPushButton*> getVueCheckable();
    vector<QPushButton*> getVueChecked();
    vector<VueCarte*> getVueCarte();
    vector<VueCarte*> getVueCarteReserve(){return vueCarteReserve;}
    vector<VueCarte*> getVueNobles(){return vueCarteNobles;};
    vector<VueCarte*> getVueCarteDev();
    vector<VueCarte*> getVueCarteDev(int i);
    vector<VuePioche*> getVuePioche();
    //utilitaire
    void UncheckVue();
};

#endif // SETVUE_H
