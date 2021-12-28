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

    string file_contents;
    string record;
    ressources couts;
    ressources bonus;
    int pdv;
    std::string path = "C:/Users/33651/Documents/Cours/LO21/splendorlo21/splendor/Deck_cartes/";
    map<Type, string> noms_files= {
        {Type::un, path+"Niveau1.csv"},
        {Type::deux , path+"Niveau2.csv"},
        {Type::trois, path+"Niveau3.csv"},
        {Type::nobles, path+"Nobles.csv"}};

    for (auto pair_type_nom : noms_files){
        file_contents = readFileIntoString(pair_type_nom.second);
        std::istringstream file_stream(file_contents);
        while(std::getline(file_stream, record)){
            std::istringstream line(record);

            switch(pair_type_nom.first)
            {
                case Type::un:
                case Type::deux:
                case Type::trois:
                    read_line_carteDev(line, pair_type_nom.first, couts, bonus, pdv);
                    cartes[pair_type_nom.first].push_back(new CarteDeveloppement(couts, bonus,pair_type_nom.first    , pdv));
                    break;
                case Type::nobles:
                    read_line_carteC_pdv(line, pair_type_nom.first, couts, pdv);
                    cartes[pair_type_nom.first].push_back(new CarteNoble(couts, pdv));
                    break;
                case Type::cite:
                    read_line_carteC_pdv(line, pair_type_nom.first, couts, pdv);
                    cartes[pair_type_nom.first].push_back(new CarteCite(couts, pdv));
                    break;
                default:
                    stringstream info;
                    info << "Type non prit en compte."<<endl;
                    info << toString(pair_type_nom.first)<<endl;
                    throw SplendorException(info.str());
            }
        }
    }
}

}
