#ifndef VUERENDUJETONS_H
#define VUERENDUJETONS_H

#include <QSpinBox>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <string>
#include <QGroupBox>
#include <QLCDNumber>
#include "./src/controleur/controleur.h"


class VueRenduJetons : public QWidget
{
    Q_OBJECT
    int nb_jetons_a_rendre;

    // - - - - Jeton - - - -
    QLabel* descriptionText;
    QHBoxLayout* layoutInformations;
    QHBoxLayout* indicatorLayout;
    QVBoxLayout* mainLayout;

    QGroupBox *aRendreBox();
    QLCDNumber* ressourceARendreLCD;

    QGroupBox *renduBox();
    QLCDNumber* renduLCD;


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
    QPushButton* jokerBouton;
     // - - - - end Jeton - - - -

    QHBoxLayout* buttonLayout;
    QPushButton* validButton;
    QPushButton* resetButton;

public slots :
    void retirerEmeraude();
    void retirerSaphir();
    void retirerRubis();
    void retirerDiamant();
    void retirerOnyx();
    void retirerJoker();

public:
    explicit VueRenduJetons(Splendor::Joueur* j, QWidget* parent = nullptr);

};


#endif // VUERENDUJETONS_H
