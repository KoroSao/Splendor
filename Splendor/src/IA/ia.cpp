#include "ia.h"


namespace Splendor
{
IA IA::NewIA(int id, Controleur* controleur){
    const array<const string, 4> nom_possible = {"IA_François", "IA_Arthur", "IA_Emma", "IA_Romain"};
    string nom = nom_possible[rand()%4];
    return IA(id, nom, controleur);
}

void IA_Simple::JouerSonTour(){
    if (nb_carte_reserve() <1){
        reserver_une_carte();
    }
    else{
        if (getReserve()[0]->canBeBougth(*this)){
            achat_carte_reserve();
        }
        else{
            prendre_jeton();
        }

    }
}

int IA_Simple::nb_carte_reserve(){
    return getReserve().size();
}

void IA_Simple::reserver_une_carte(){
    if (getPDV() < 2){
        reserver_carte_niveauI();
    }
    else if(getPDV() <6){
        reserver_carte_niveauII();
    }
    else{
        reserver_carte_niveauIII();
    }
}

void IA_Simple::reserver_carte_niveauI(){
    if (nb_carte_remporte() == 0){
        reserver_premier_carte();
    }
    else{
        vector<const Carte *> cartes_niveauI = controleur->getPlateau().getNiveauDeveloppement(1).getCartes();
        reserver_meilleur_carte(cartes_niveauI);
    }
}
void IA_Simple::reserver_carte_niveauII(){
    vector<const Carte *> cartes_niveauII = controleur->getPlateau().getNiveauDeveloppement(2).getCartes();
    reserver_meilleur_carte(cartes_niveauII);
}

void IA_Simple::reserver_carte_niveauIII(){
    vector<const Carte *> cartes_niveauIII = controleur->getPlateau().getNiveauDeveloppement(3).getCartes();
    reserver_meilleur_carte(cartes_niveauIII);
}

void IA_Simple::reserver_premier_carte(){
    vector<const Carte *> cartes_niveauI = controleur->getPlateau().getNiveauDeveloppement(1).getCartes();
    for (auto carte: cartes_niveauI){
        if (remplis_critere_achat_premier_carte(carte)){
            controleur->reserverCarte(*this, *carte);
            return;
        }
    }
    //par defaut on reserve la premiere du niveau
    controleur->reserverCarte(*this, *cartes_niveauI[0]);
}

bool IA_Simple::remplis_critere_achat_premier_carte(const Carte *carte){
    int nb_jetons_cout = 0;
    for (size_t i=0;i<5; i++ )nb_jetons_cout+= carte->getCouts(i);
    bool plsr_types_jetons = false;
    for (size_t i=0;i<5&&!plsr_types_jetons; i++ )plsr_types_jetons = (carte->getCouts(i)!=0 && carte->getCouts(i)!=nb_jetons_cout);
    return ((nb_jetons_cout <=3 && !plsr_types_jetons)
        ||(nb_jetons_cout <=4 && plsr_types_jetons));

}

void IA_Simple::reserver_meilleur_carte(vector<const Carte *> &cartes){
    vector<int> nb_tours_pour_achat;
    for (auto carte : cartes){
        nb_tours_pour_achat.push_back(estimation_nb_tour_achat(carte));
    }
    size_t indice_achat_rapide = indice_min(nb_tours_pour_achat);
    controleur->reserverCarte(*this, *cartes[indice_achat_rapide]);
}

int IA_Simple::estimation_nb_tour_achat(const Carte *carte){
    ressources jetons_a_acquerir = jetons_manquant_pour_achat(carte);
    int nb_tours_estime = 0;
    int nb_prise_un_jetons = 0;

    for (auto nb_jetons : jetons_a_acquerir) {
        nb_tours_estime += nb_jetons/2;
        nb_prise_un_jetons += nb_jetons%2;
    }
    nb_tours_estime += nb_prise_un_jetons/3 + 1;
    return nb_tours_estime;
}

ressources IA_Simple::jetons_manquant_pour_achat(const Carte* carte){
    ressources jetons_a_acquerir;
    for (size_t i=0;i<5; i++ )jetons_a_acquerir[i] = max(0, carte->getCouts(i)-(int)getBonus(i));
    return jetons_a_acquerir;
}

size_t IA_Simple::indice_min(vector<int> entiers){
    size_t indice_min = 0;
    for (size_t i = 0;i<entiers.size(); i++){
        if (entiers[i]< entiers[indice_min]) indice_min = i;
    }
    return indice_min;
}

void IA_Simple::achat_carte_reserve(){
    controleur->acheterCarte(*this, *getReserve()[0]);
}

void IA_Simple::prendre_jeton(){
    prise_jetons(choix_prise_jetons());
}

vector<int> IA_Simple::choix_prise_jetons(){
    vector<int> indice_jetons_a_prendre;
    ressources jetons_manquants = jetons_manquant_pour_achat(getReserve()[0]);
    for (size_t i = 0; i<5;i++){
        if (jetons_manquants[i]>=2){
            indice_jetons_a_prendre.push_back(i);
            return indice_jetons_a_prendre;
        }
    }
    for (size_t i=0;i<5;i++){
        if (jetons_manquants[i] != 0){
            indice_jetons_a_prendre.push_back(i);
        }
    }
    return indice_jetons_a_prendre;
}

void IA_Simple::prise_jetons(vector<int> id_jetons){
    if (id_jetons.size()==1){
        if (controleur->getPlateau().getBanque(id_jetons[0])!=0){
            controleur->prendreRessource(*this, id_jetons[0]);
        }
        if (controleur->getPlateau().getBanque(id_jetons[0])>3)
            controleur->prendreRessource(*this, id_jetons[0]);
    }
    for(size_t i =0; i< min(3, (int)id_jetons.size());i++){
        if (controleur->getPlateau().getBanque(id_jetons[i])){
            controleur->prendreRessource(*this, id_jetons[i]);
        }
    }
}
}

