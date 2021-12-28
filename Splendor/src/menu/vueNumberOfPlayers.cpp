#include "vueNumberOfPlayers.h"
#include "vuePlayerConfig.h"

vueNumberOfPlayers::vueNumberOfPlayers(QWidget *parent): QWidget(parent)
{
    layoutPrincipal = new QVBoxLayout;

    //choisir nombre de joueurs
    spinBoxLayout = new QVBoxLayout;
    integerLabel = new QLabel(tr("Nombre de joueurs entre "
        "%1 et %2:").arg(2).arg(4));

    integerSpinBox = new QSpinBox;
    integerSpinBox->setRange(2, 4);
    integerSpinBox->setSingleStep(1);
    integerSpinBox->setValue(2);
    spinBoxLayout->addWidget(integerLabel);
    spinBoxLayout->addWidget(integerSpinBox);

    //Demander si jeu normal ou extension
    choiceLayout = new QVBoxLayout;
    phrase = new QLabel(tr("Voulez vous jouer la version classique ou l'extension cite"));
    choixjeu = new QComboBox;
    choixjeu->addItem("Version classique");
    choixjeu->addItem("Extension cite");
    choiceLayout->addWidget(phrase);
    choiceLayout->addWidget(choixjeu);

    //Bouton Valider
    bouton = new QPushButton("Valider", this);


    //encapsuler les trois derniers layout
    layoutPrincipal -> addLayout(spinBoxLayout);
    layoutPrincipal -> addLayout(choiceLayout);
    layoutPrincipal -> addWidget(bouton);
    setLayout(layoutPrincipal);

    //envoyer vers fenêtre suivante
    QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(suivant()));
}

void vueNumberOfPlayers::suivant(){
    int nbJoueurs = integerSpinBox->value();
    int choix = choixjeu->currentIndex();
    //si choix = 0 alors version normale, si choix =1 alors extension
    vuePlayerConfig* fenetre= new vuePlayerConfig(choix,nbJoueurs);
    fenetre->show();
    hide();
}


