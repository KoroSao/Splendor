#include "setvue.h"
#include <string>

using namespace Splendor;

SetVue::SetVue(int nb_joueur)
{
    dictionnaireVues["cartesDevI"] = vector<QPushButton*>(4, new VueCarte);
    dictionnaireVues["cartesDevII"] = vector<QPushButton*>(4, new VueCarte);
    dictionnaireVues["cartesDevIII"] = vector<QPushButton*>(4, new VueCarte);
    dictionnaireVues["cartesNobles"] = vector<QPushButton*>(nb_joueur+1, new VueCarte);
    dictionnaireVues["pioches"] = vector<QPushButton*>(3, new VuePioche);
}

vector<QPushButton*> SetVue::getCheckable(){
    vector<QPushButton*> checkable;
    vector<std::string> categorieCheckable = {"carteDevI", "carteDevII", "carteDevIII", "pioches"};
    for (std::string& cat : categorieCheckable){
        for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
            checkable.push_back(dictionnaireVues[cat][j]);
        }
    }
    return checkable;
}

vector<VueCarte*> SetVue::getVueCarte(){
    vector<VueCarte*> vuecartes;
    vector<string> categorieVueCarte = {"carteDevI", "carteDevII", "carteDevIII", "carteNobles"};
    for (std::string& cat : categorieVueCarte){
        for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
            vuecartes.push_back(dynamic_cast<VueCarte*>( dictionnaireVues[cat][j]));
        }
    }
    return vuecartes;

}

vector<VueCarte*> SetVue::getVueCarteDev(){
    vector<VueCarte*> vuecartes;
    vector<string> categorieVueCarte = {"carteDevI", "carteDevII", "carteDevIII"};
    for (std::string& cat : categorieVueCarte){
        for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
            vuecartes.push_back(dynamic_cast<VueCarte*>( dictionnaireVues[cat][j]));
        }
    }
    return vuecartes;
}

vector<VueCarte*> SetVue::getVueCarteDev(int i ){
    if (i<0 || i>3) throw SplendorException(
                "Splendor::SetVue::getVueCarteDev(int i ) : argument i invalide : "+to_string(i));
    vector<VueCarte*> vuecartes;
    vector<string> categorieVueCarte = {"carteDevI", "carteDevII", "carteDevIII", "carteNobles"};
    std::string cat = categorieVueCarte[i];
    for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
        vuecartes.push_back(dynamic_cast<VueCarte*>( dictionnaireVues[cat][j]));
    }
    return vuecartes;
}

vector<VueCarte*> SetVue::getVueNobles(){
    vector<VueCarte*> vuecartes;
    std::string cat = "carteNobles";
    for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
        vuecartes.push_back(dynamic_cast<VueCarte*>( dictionnaireVues[cat][j]));
    }
    return vuecartes;

}

vector<VuePioche*> SetVue::getVuePioche(){
    vector<VuePioche*> vuepioche;
    std::string cat = "pioches";
    for (size_t j = 0; j<dictionnaireVues[cat].size(); j++){
        vuepioche.push_back(dynamic_cast<VuePioche*>( dictionnaireVues[cat][j]));
    }
    return vuepioche;

}
