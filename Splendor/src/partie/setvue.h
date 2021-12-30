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
    map<std::string, vector<QPushButton*>> dictionnaireVues;
public:
    SetVue(int);
    vector<QPushButton*> getCheckable();
    vector<VueCarte*> getVueCarte();
    vector<VueCarte*> getVueNobles();
    vector<VueCarte*> getVueCarteDev();
    vector<VueCarte*> getVueCarteDev(int i);
    vector<VuePioche*> getVuePioche();
};

#endif // SETVUE_H
