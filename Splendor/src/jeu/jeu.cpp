#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <array>
#include <QString>
#include <QDir>
#include "jeu.h"
//#include <filesystem>
//#include <unistd.h>
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

string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

void read_line_carteDev(std::istringstream& line,Type type,
                        ressources& couts,ressources& bonus, int& pdv){
    char delimiter = ',';
    string record;
    read_line_carteC_pdv(line, type, couts, pdv);
    for (size_t i = 0; i<5; i++){
        std::getline(line, record, delimiter);
        std::stringstream(record) >> bonus[i];
    }

}

void read_line_carteC_pdv(std::istringstream& line,Type type, ressources& couts, int& pdv){
    char delimiter = ',';
    string record;
    std::getline(line, record, delimiter);
    if (record != toString(type)) {
            std::stringstream infos;
            infos <<"Fichier mal forme."<<endl;
            infos <<"Type de carte demande :"<<toString(type)<<endl;
            infos <<"Type donne dans le fichier : "<<record<<endl;
            throw SplendorException(infos.str());
    }
    for (size_t i = 0; i<5; i++){
        std::getline(line, record, delimiter);
        std::stringstream(record) >> couts[i];
    }
    std::getline(line, record, delimiter);
    std::stringstream(record) >> pdv;
}

Jeu::Jeu(){


    string file_contents;
    string record;
    ressources couts;
    ressources bonus;
    int pdv;

    const auto filePath = QDir::currentPath();

    string tmp2 = filePath.toStdString();
    while(tmp2[tmp2.size()-1]!='/')
      tmp2.pop_back();

    std::string path = tmp2 + "Splendor/Deck_cartes/";

    /*
     Commentaire pour le prof: Si vuous avez une erreur de chargement des fichiers CSV
     lors de la compilation, ci-dessous sont 3 exemples de chemins fonctionnels:
     - sous Linux
     - sous MacOS
     - sous Windows
      */

    //std::string path = "/home/romain/Documents/GI01/LO21/Projet/splendorlo21/Splendor/Deck_cartes/";
    //std::string path = "/Users/ax_art/Desktop/LO21/Projet/gitlab/splendorlo21/Splendor/Deck_cartes/";
    //std::string path = "C:\\Users\\33651\\Documents\\Cours\\LO21\\splendorlo21\\splendor\\Deck_cartes\\";
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
