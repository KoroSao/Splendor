#include "vueRenduJetons.h"


VueRenduJetons::VueRenduJetons(Splendor::Joueur* j, QDialog *parent): QDialog(parent)
{
    descriptionText = new QLabel(tr("Veuillez choisir quelles ressources rendre, vous en avez trop ! Vous devez en rendre exactement le nombre indiqué."));

    nb_jetons_a_rendre = -10;
    for (auto i = 0; i < 6; i ++){
        nb_jetons_a_rendre += j->getInventaire(i);
    }

    QGroupBox *emeraudeBox = new QGroupBox(tr("Emeraude :"));
    QHBoxLayout *emeraudeLayout = new QHBoxLayout;
    QGroupBox *saphirBox = new QGroupBox(tr("Saphir :"));
    QHBoxLayout *saphirLayout = new QHBoxLayout;
    QGroupBox *rubisBox = new QGroupBox(tr("Rubis :"));
    QHBoxLayout *rubisLayout = new QHBoxLayout;
    QGroupBox *diamantBox = new QGroupBox(tr("Diamant :"));
    QHBoxLayout *diamantLayout = new QHBoxLayout;
    QGroupBox *onyxBox = new QGroupBox(tr("Onyx :"));
    QHBoxLayout *onyxLayout = new QHBoxLayout;
    QGroupBox *jokerBox = new QGroupBox(tr("Joker :"));
    QHBoxLayout *jokerLayout = new QHBoxLayout;

    QHBoxLayout* indicatorLayout = new QHBoxLayout();

    QGroupBox * aRendreBox = new QGroupBox(tr("Nombre de ressources à rendre"));
    QHBoxLayout* aRendreLayout = new QHBoxLayout;
    ressourceARendreLCD = new QLCDNumber;
    ressourceARendreLCD->setFixedHeight(30);
    ressourceARendreLCD->setFixedWidth(80);
    ressourceARendreLCD->display(QString::number(nb_jetons_a_rendre));
    aRendreLayout->addWidget(ressourceARendreLCD);
    aRendreBox->setLayout(aRendreLayout);

    indicatorLayout->addWidget(aRendreBox);

    QGroupBox* renduBox = new QGroupBox(tr("Nombre de ressources que vous rendez actuellement"));
    QHBoxLayout* renduLayout = new QHBoxLayout;
    renduLCD = new QLCDNumber;
    renduLCD->setFixedHeight(30);
    renduLCD->setFixedWidth(80);
    renduLCD->display(QString::number(0));
    renduLayout->addWidget(renduLCD);
    renduBox->setLayout(renduLayout);

    indicatorLayout->addWidget(renduBox);

    //QGroupBox *ressourceRendues();
    //QLCDNumber* ressourceRenduesLCD;

    emeraudeBanque=new QLCDNumber;
    emeraudeBanque->display(QString::number(j->getInventaire(0)));
    emeraudeBanque->setFixedHeight(30);
    emeraudeLayout->addWidget(emeraudeBanque);
    saphirBanque=new QLCDNumber;
    saphirBanque->display(QString::number(j->getInventaire(1)));
    saphirBanque->setFixedHeight(30);
    saphirLayout->addWidget(saphirBanque);
    rubisBanque=new QLCDNumber;
    rubisBanque->display(QString::number(j->getInventaire(2)));
    rubisBanque->setFixedHeight(30);
    rubisLayout->addWidget(rubisBanque);
    diamantBanque=new QLCDNumber;
    diamantBanque->display(QString::number(j->getInventaire(3)));
    diamantBanque->setFixedHeight(30);
    diamantLayout->addWidget(diamantBanque);
    onyxBanque=new QLCDNumber;
    onyxBanque->display(QString::number(j->getInventaire(4)));
    onyxBanque->setFixedHeight(30);
    onyxLayout->addWidget(onyxBanque);
    jokerBanque=new QLCDNumber;
    jokerBanque->display(QString::number(j->getInventaire(5)));
    jokerBanque->setFixedHeight(30);
    jokerLayout->addWidget(jokerBanque);

    emeraudeBouton = new QPushButton("Rendre", this);
    emeraudeBouton->setFixedSize(QSize(75, 42));
    emeraudeLayout->addWidget(emeraudeBouton);
    saphirBouton = new QPushButton("Rendre", this);
    saphirBouton->setFixedSize(QSize(75, 42));
    saphirLayout->addWidget(saphirBouton);
    rubisBouton = new QPushButton("Rendre", this);
    rubisBouton->setFixedSize(QSize(75, 42));
    rubisLayout->addWidget(rubisBouton);
    diamantBouton = new QPushButton("Rendre", this);
    diamantBouton->setFixedSize(QSize(75, 42));
    diamantLayout->addWidget(diamantBouton);
    onyxBouton = new QPushButton("Rendre", this);
    onyxBouton->setFixedSize(QSize(75, 42));
    onyxLayout->addWidget(onyxBouton);
    jokerBouton = new QPushButton("Rendre", this);
    jokerBouton ->setFixedSize(QSize(75, 42));
    jokerLayout->addWidget(jokerBouton);

    layoutInformations=new QHBoxLayout;

    emeraudeBox->setLayout(emeraudeLayout);
    layoutInformations->addWidget(emeraudeBox);
    saphirBox->setLayout(saphirLayout);
    layoutInformations->addWidget(saphirBox);
    rubisBox->setLayout(rubisLayout);
    layoutInformations->addWidget(rubisBox);
    diamantBox->setLayout(diamantLayout);
    layoutInformations->addWidget(diamantBox);
    onyxBox->setLayout(onyxLayout);
    layoutInformations->addWidget(onyxBox);
    jokerBox->setLayout(jokerLayout);
    layoutInformations->addWidget(jokerBox);

    //Bouton Valider
    buttonLayout = new QHBoxLayout;
    validButton = new QPushButton("Valider", this);
    resetButton = new QPushButton("Reset", this);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(validButton);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionText);
    mainLayout->addLayout(indicatorLayout);
    mainLayout->addLayout(layoutInformations);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    //envoyer vers fenêtre suivante
    connect(
                validButton, &QPushButton::clicked,
                [=]() {
                    if (renduLCD->intValue() == nb_jetons_a_rendre){
                        j->setInventaire(0, emeraudeBanque->intValue());
                        j->setInventaire(1, saphirBanque->intValue());
                        j->setInventaire(2, rubisBanque->intValue());
                        j->setInventaire(3, diamantBanque->intValue());
                        j->setInventaire(4, onyxBanque->intValue());
                        j->setInventaire(5, jokerBanque->intValue());
                        j->afficherInventaire();
                        hide();
                    }

            }
            );

    connect(
                resetButton, &QPushButton::clicked,
                [=]() {
                    emeraudeBanque->display(QString::number(j->getInventaire(0)));
                    saphirBanque->display(QString::number(j->getInventaire(1)));
                    rubisBanque->display(QString::number(j->getInventaire(2)));
                    diamantBanque->display(QString::number(j->getInventaire(3)));
                    onyxBanque->display(QString::number(j->getInventaire(4)));
                    jokerBanque->display(QString::number(j->getInventaire(5)));
                    renduLCD->display(0);
            }
            );
    //QObject::connect(validButton, SIGNAL(clicked()), this, SLOT(suivant(j)));
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset(j)));
    QObject::connect(emeraudeBouton, SIGNAL(clicked()), this, SLOT(retirerEmeraude()));
    QObject::connect(saphirBouton, SIGNAL(clicked()), this, SLOT(retirerSaphir()));
    QObject::connect(rubisBouton, SIGNAL(clicked()), this, SLOT(retirerRubis()));
    QObject::connect(diamantBouton, SIGNAL(clicked()), this, SLOT(retirerDiamant()));
    QObject::connect(onyxBouton, SIGNAL(clicked()), this, SLOT(retirerOnyx()));
    QObject::connect(jokerBouton, SIGNAL(clicked()), this, SLOT(retirerJoker()));
}



void VueRenduJetons::retirerEmeraude(){
    if (emeraudeBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        emeraudeBanque->display(emeraudeBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}

void VueRenduJetons::retirerSaphir(){
    if (saphirBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        saphirBanque->display(saphirBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}

void VueRenduJetons::retirerRubis(){
    if (rubisBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        rubisBanque->display(rubisBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}

void VueRenduJetons::retirerDiamant(){
    if (diamantBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        diamantBanque->display(diamantBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}

void VueRenduJetons::retirerOnyx(){
    if (onyxBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        onyxBanque->display(onyxBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}

void VueRenduJetons::retirerJoker(){
    if (jokerBanque->intValue() > 0 && renduLCD->intValue() < nb_jetons_a_rendre){
        jokerBanque->display(jokerBanque->intValue() - 1);
        renduLCD->display(renduLCD->intValue() + 1);
    }
}





