#ifndef IA_H
#define IA_H

#include <array>
#include <algorithm>
#include <iostream>
#include "../controleur/controleur.h"
#include "../joueur/joueur.h"

namespace Splendor {

class abstractIA : public Joueur
{
protected:
    Controleur* const controleur;
public:
    abstractIA(int id, string nom, Controleur* controleur) : Joueur(id, nom), controleur(controleur){};
    virtual void JouerSonTour() = 0;
};

class IA : public abstractIA{
    IA(int id, string nom, Controleur* controleur) : abstractIA(id, nom, controleur){};
public :
    static IA NewIA(int id, Controleur* controleur);
    void JouerSonTour() override;
};

class IA_Simple : public IA{
public:
    void JouerSonTour() override;
private:
    int nb_carte_reserve();
    void reserver_une_carte();
    void reserver_carte_niveauI();
    void reserver_carte_niveauII();
    void reserver_carte_niveauIII();
    void achat_carte_reserve();
    ressources jetons_manquant_pour_achat(const Carte* carte);
    void prendre_jeton();
    vector<int> choix_prise_jetons();
    void prise_jetons(vector<int> id_jetons);
    int nb_carte_remporte();
    void reserver_meilleur_carte(vector<const Carte*>& cartes);
    void reserver_premier_carte();
    bool remplis_critere_achat_premier_carte(const Carte* carte);
    int estimation_nb_tour_achat(const Carte* carte);
    size_t indice_min(vector<int>);
};

}
#endif // IA_H
