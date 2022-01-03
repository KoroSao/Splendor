#include "setvue.h"
#include <string>

using namespace Splendor;

SetVue::SetVue(int nb_joueur):vueCarteDevI(4, nullptr), vueCarteDevII(4, nullptr), vueCarteDevIII(4, nullptr),
    vueCarteNobles(nb_joueur+1, nullptr), vueCarteReserve(3, nullptr), vuePioche(3, nullptr)
{
    for (size_t i = 0; i<4; i++){
        vueCarteDevI[i] = new VueCarte;
        vueCarteDevII[i] = new VueCarte;
        vueCarteDevIII[i] = new VueCarte;
    }
    for(size_t i = 0; i<3; i++){
        vueCarteReserve[i] = new VueCarte;
        vuePioche[i] = new VuePioche;
    }
    for (size_t i = 0; i<nb_joueur+1; i++){
        vueCarteNobles[i] = new VueCarte;
    }
    for (VueCarte* carteNoble : vueCarteNobles) carteNoble->setCheckable(false);
}

vector<QPushButton*> SetVue::getVueCheckable(){
    vector<QPushButton*> checkable;
    for (auto vuecarte : vueCarteDevI) checkable.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevII) checkable.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevIII) checkable.push_back(vuecarte);
    for (auto vuecarte : vueCarteReserve) checkable.push_back(vuecarte);
    for (auto vuepioche : vuePioche) checkable.push_back(vuepioche);
    return checkable;
}

vector<VueCarte*> SetVue::getVueCarte(){
    vector<VueCarte*> vuecartes;
    for (auto vuecarte : vueCarteDevI) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevII) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevIII) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteReserve) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteNobles) vuecartes.push_back(vuecarte);
    return vuecartes;

}

vector<VueCarte*> SetVue::getVueCarteDev(){
    vector<VueCarte*> vuecartes;
    for (auto vuecarte : vueCarteDevI) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevII) vuecartes.push_back(vuecarte);
    for (auto vuecarte : vueCarteDevIII) vuecartes.push_back(vuecarte);
    return vuecartes;

}

vector<VueCarte*> SetVue::getVueCarteDev(int i ){
    switch(i){
    case 0 :
        return vueCarteDevI;
    case 1:
        return vueCarteDevII;
    case 2:
        return vueCarteDevIII;
    default:
        throw SplendorException("SetVue::getVueCarteDev(int i) invalide parameter i : "+to_string(i));
    }
}
vector<VuePioche*> SetVue::getVuePioche(){
    vector<VuePioche*> vuepioches;
    for (auto vuepioche : vuePioche) vuepioches.push_back(vuepioche);
    return vuepioches;

}


vector<QPushButton*> SetVue::getVueChecked(){
    vector<QPushButton*> vueCheckable = getVueCheckable();
    vector<QPushButton*> vueChecked;
    for (size_t j = 0; j<vueCheckable.size(); j++){
        if (vueCheckable[j]->isChecked())
            vueChecked.push_back(vueCheckable[j]);
    }
    return vueChecked;
}

void SetVue::UncheckVue(){
    vector<QPushButton*> vueChecked = getVueChecked();
    for (size_t j = 0; j<vueChecked.size(); j++){
        vueChecked[j]->setChecked(false);
    }

}
