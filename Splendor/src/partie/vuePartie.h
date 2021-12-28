#ifndef VUEPARTIE_H
#define VUEPARTIE_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <vector>
#include <set>
#include <string.h>
#include "../controleur/controleur.h"
#include "vueCarte.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QProgressBar;
class QLCDNumber;
class VueCarte;

using namespace Splendor;

class VuePartie : public QWidget {
    Q_OBJECT
public:
    explicit VuePartie(unsigned int nbj, vector<std::string> names, QWidget *parent = nullptr);
    void updateJoueurInfo();
    void updatePlateauInfo();

private:

    Splendor::Controleur controleur; // controleur de la partie //TODO: fixé à 4 joueurs
    int nbJetonsPris = 0;
    int jetonsPris[5] = {0,0,0,0,0};
    bool sameJetonPris = false;
    bool cartePrise = false;

    const Splendor::Carte* selectionCarte = nullptr;


    // - - - - Jeton - - - -
    QGroupBox *emeraudeBox();
    QLCDNumber* emeraudeBanque;
    QPushButton *emeraudeBouton;

    QGroupBox *saphirBox();
    QLCDNumber* saphirBanque;
    QPushButton *saphirBouton;

    QGroupBox *rubisBox();
    QLCDNumber* rubisBanque;
    QPushButton *rubisBouton;

    QGroupBox *diamantBox();
    QLCDNumber* diamantBanque;
    QPushButton *diamantBouton;

    QGroupBox *onyxBox();
    QLCDNumber* onyxBanque;
    QPushButton *onyxBouton;

    QGroupBox *jokerBox();
    QLCDNumber* jokerBanque;
     // - - - - end Jeton - - - -

    QLabel* banque; // texte
    QLabel* carteNobles; // texte
    QLabel* playersData; // texte

    QVBoxLayout* playersBox;
    QVBoxLayout* playerLayout;
    QGroupBox* playersDataBox();

    QGroupBox* currentPlayerBox;
    QHBoxLayout* currentPlayerLayout;
    QGroupBox* currentPlayerRessourceBox;
    QVBoxLayout* currentPlayerRessourceLayout;
    QGroupBox* inventaireCurrentPlayerBox();
    QGroupBox* bonusCurrentPlayerBox();
    QGroupBox* pdvCurrentPlayerBox();
    QVBoxLayout *pdvCurrentPlayerLayout;
    QLCDNumber *pdvCurrentPlayer;
    QGroupBox* reserveCurrentPlayerBox();

    QHBoxLayout *inventaireCurrentPlayerLayout;
    QLCDNumber *emeraudeCurrentPlayer;
    QLCDNumber *saphirCurrentPlayer;
    QLCDNumber *rubisCurrentPlayer;
    QLCDNumber *diamantCurrentPlayer;
    QLCDNumber *onyxCurrentPlayer;
    QLCDNumber *jokerCurrentPlayer;

    QHBoxLayout *bonusCurrentPlayerLayout;
    QLCDNumber *emeraudeCurrentBonusPlayer;
    QLCDNumber *saphirCurrentBonusPlayer;
    QLCDNumber *rubisCurrentBonusPlayer;
    QLCDNumber *diamantCurrentBonusPlayer;
    QLCDNumber *onyxCurrentBonusPlayer;

    QHBoxLayout* layoutInformations;
    QGridLayout* layoutCartes; // grille des cartes
    QGridLayout* layoutCartesNobles;
    QGridLayout* layoutCartesReserve;
    QVBoxLayout* couche;

    QPushButton *pioche1Bouton;
    QPushButton *pioche2Bouton;
    QPushButton *pioche3Bouton;

    QGroupBox* playerActionBox();
    QVBoxLayout* playerActionLayout();
    QPushButton* endTurnBouton;
    QPushButton* cancelTurnBouton;

    vector<VueCarte*> vuecartes; // adresses des objets VueCarte
    vector<VueCarte*> vuecartesNobles; // adresses des objets VueCarteNobles

    vector<VueCarte*> vuecartesReserve; //adresses des cartes reserver par le joueur

    std::set<const Splendor::Carte*> selectionCartes; // ensemble des cartes sélectionnées


    private slots:
        // slots qui gère les clics sur les cartes et boutons
        void carteClique(VueCarte* vc);
        void emeraudeBoutonClique();
        void saphirBoutonClique();
        void rubisBoutonClique();
        void diamantBoutonClique();
        void onyxBoutonClique();
        void pioche1BoutonClique();
        void pioche2BoutonClique();
        void pioche3BoutonClique();
        void cancelTurnClique();
        void endTurnClique();

};

#endif
