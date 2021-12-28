#include "vuePlayerConfig.h"
#include "./src/controleur/controleur.h"

vuePlayerConfig::vuePlayerConfig(int choix, int nbJoueurs, QWidget *parent): QWidget(parent), choix(choix), nbJoueurs (nbJoueurs)
{
    layoutPrinc = new QVBoxLayout;
    for (int i=0; i<nbJoueurs; i++)
    {
        //vérifier si IA ou Humain
        layout=new QHBoxLayout;
        sentence = new QLabel(tr("Choisissez le type du joueur %1").arg(i));
        choixtype = new QComboBox;
        choixtype->addItem("Humain");
        choixtype->addItem("IA Equilibré");
        choixtype->addItem("IA Spécialisé");
        choixtype->addItem("IA Antoine Jouglet");

        layout->addWidget(sentence);
        layout->addWidget(choixtype);



        iahumain.push_back(layout);

        //Demander le nom désiré pour les IA et les joueurs
        name = new QLineEdit(nullptr);
        name -> setPlaceholderText("Nom joueur:");


        layout->addWidget(name);
        layoutPrinc->addLayout(layout);
    }
    // appuyer sur le bouton valider
    bouton = new QPushButton("Valider", this);
    layoutPrinc->addWidget(bouton);

    setLayout(layoutPrinc);

    //envoyer vers fenêtre suivante
    QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(suivant()));

}

void vuePlayerConfig::suivant(){
    std::cout << "Nombre de joueurs : " << nbJoueurs << std::endl;
    std::cout << "Extension : " << choix << std::endl;
    for (auto i =0; i < nbJoueurs; i++){
        string name = qobject_cast<QLineEdit*>(iahumain[i]->itemAt(2)->widget())->text().toStdString();
        string type = qobject_cast<QComboBox*>(iahumain[i]->itemAt(1)->widget())->currentText().toStdString();
        noms.push_back(name);
        types.push_back(type);
    }

    //Ici nous avons toutes les infos pour lancer le controleur !
    VuePartie* game = new VuePartie(nbJoueurs, noms);
    game->show();
    hide();
}

vuePlayerConfig::~vuePlayerConfig()
{
    for(auto p : iahumain)
    {
        delete p;
    }

}
