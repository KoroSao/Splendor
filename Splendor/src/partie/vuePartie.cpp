#include <QLabel>
//#include <QlineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "./vuePartie.h"
#include "vueCarte.h"


using namespace Splendor;

VuePartie::VuePartie(unsigned int nbj, vector<std::string> names, QWidget *parent) :
    QWidget(parent), controleur(nbj,names) ,vuecartes(20,nullptr), vuecartesNobles(5,nullptr), vuecartesReserve(3,nullptr)
{
    setWindowTitle("Splendor !"); // modifier le titre de la fenêtre
    banque = new QLabel("Banque:"); //(émeraude/saphir/rubis/diamant/onyx/joker)

    carteNobles = new QLabel("Carte Nobles : ");

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

    emeraudeBanque=new QLCDNumber;
    emeraudeBanque->display(QString::number(controleur.getPlateau().getBanque(0)));
    emeraudeBanque->setFixedHeight(30);
    emeraudeLayout->addWidget(emeraudeBanque);
    saphirBanque=new QLCDNumber;
    saphirBanque->display(QString::number(controleur.getPlateau().getBanque(1)));
    saphirBanque->setFixedHeight(30);
    saphirLayout->addWidget(saphirBanque);
    rubisBanque=new QLCDNumber;
    rubisBanque->display(QString::number(controleur.getPlateau().getBanque(2)));
    rubisBanque->setFixedHeight(30);
    rubisLayout->addWidget(rubisBanque);
    diamantBanque=new QLCDNumber;
    diamantBanque->display(QString::number(controleur.getPlateau().getBanque(3)));
    diamantBanque->setFixedHeight(30);
    diamantLayout->addWidget(diamantBanque);
    onyxBanque=new QLCDNumber;
    onyxBanque->display(QString::number(controleur.getPlateau().getBanque(4)));
    onyxBanque->setFixedHeight(30);
    onyxLayout->addWidget(onyxBanque);
    jokerBanque=new QLCDNumber;
    jokerBanque->display(QString::number(controleur.getPlateau().getBanque(5)));
    jokerBanque->setFixedHeight(30);
    jokerLayout->addWidget(jokerBanque);

    emeraudeBouton = new QPushButton("Prendre", this);
    emeraudeBouton->setFixedSize(QSize(75, 42));
    emeraudeLayout->addWidget(emeraudeBouton);
    saphirBouton = new QPushButton("Prendre", this);
    saphirBouton->setFixedSize(QSize(75, 42));
    saphirLayout->addWidget(saphirBouton);
    rubisBouton = new QPushButton("Prendre", this);
    rubisBouton->setFixedSize(QSize(75, 42));
    rubisLayout->addWidget(rubisBouton);
    diamantBouton = new QPushButton("Prendre", this);
    diamantBouton->setFixedSize(QSize(75, 42));
    diamantLayout->addWidget(diamantBouton);
    onyxBouton = new QPushButton("Prendre", this);
    onyxBouton->setFixedSize(QSize(75, 42));
    onyxLayout->addWidget(onyxBouton);

    //colorisation des ressources
    emeraudeBox->setStyleSheet("border : 1px solid green");
    saphirBox->setStyleSheet("border : 1px solid blue");
    rubisBox->setStyleSheet("border : 1px solid red");
    diamantBox->setStyleSheet("border : 1px solid white");
    onyxBox->setStyleSheet("border : 1px solid black");
    jokerBox->setStyleSheet("border : 1px solid gold");

    layoutInformations=new QHBoxLayout;
    layoutCartes = new QGridLayout;
    layoutCartesNobles = new QGridLayout;
    layoutCartesReserve = new QGridLayout;
    couche = new QVBoxLayout;

    //Informations
    layoutInformations->addWidget(banque);

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

    //Gestion des Pioches 1 2 et 3
    pioche1Bouton = new QPushButton("Pioche1", this);
    pioche1Bouton->setFixedSize(QSize(60, 100));

    pioche2Bouton = new QPushButton("Pioche2", this);
    pioche2Bouton->setFixedSize(QSize(60, 100));

    pioche3Bouton = new QPushButton("Pioche3", this);
    pioche3Bouton->setFixedSize(QSize(60, 100));

    layoutCartes->addWidget(pioche1Bouton,0,0);
    layoutCartes->addWidget(pioche2Bouton,1,0);
    layoutCartes->addWidget(pioche3Bouton,2,0);

    //création des vues des cartesDeveloppement
    for(size_t i=0; i<12;i++)
        vuecartes[i] = new VueCarte;
    for(size_t i=0; i<12;i++){
        layoutCartes->addWidget(vuecartes[i],((i)/4),((i)%4)+1);//ajout de la carte sur la grille
        connect(vuecartes[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
    }

    size_t nb_joueur = controleur.getNbJoueurs();

    //création des vues des cartesNobles
    for(size_t i=0; i<nb_joueur + 1;i++)
        vuecartesNobles[i] = new VueCarte;
    for(size_t i=0; i<nb_joueur + 1;i++){
        layoutCartesNobles->addWidget(vuecartesNobles[i],i/(nb_joueur+1),i%(nb_joueur+1));//ajout de la carte sur la grille
        connect(vuecartesNobles[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteNobleClique(VueCarte*)));
    }

    //affectation des cartes du plateau aux vues des cartes
    size_t i = 0;

    //Carte de développement
    for(int j = 0; j<3; j++){
        for(auto it: controleur.getPlateau().getNiveauDeveloppement(j).getCartes()){
            //it->afficherCarte();
            vuecartes[i]->setCarte(*it);
            i++;
        }
    }

    //Carte Nobles
    size_t j = 0;
    for(auto it: controleur.getPlateau().getNiveauNobles().getCartes()){
        vuecartesNobles[j]->setCarte(*it);
        j++;
    }

    QVBoxLayout *playerLayout = new QVBoxLayout();


    currentPlayerBox = new QGroupBox(QString::fromStdString(controleur.getJoueur(controleur.getCurrentPlayer()).getNom())); //TODO:: add name current player
    currentPlayerBox->setStyleSheet("QGroupBox{ font-weight: bold }");

    QHBoxLayout* currentPlayerLayout = new QHBoxLayout();
    QGroupBox* currentPlayerRessourceBox = new QGroupBox();
    QVBoxLayout* currentPlayerRessourceLayout = new QVBoxLayout();

    QGroupBox* inventaireCurrentPlayerBox = new QGroupBox(tr("Inventaire"));
    QGroupBox* bonusCurrentPlayerBox = new QGroupBox(tr("Bonus"));

    QHBoxLayout *inventaireCurrentPlayerLayout = new QHBoxLayout;
    QHBoxLayout *bonusCurrentPlayerLayout = new QHBoxLayout;
////// START QLCD
    emeraudeCurrentPlayer=new QLCDNumber;
    emeraudeCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(0)));
    emeraudeCurrentPlayer->setFixedHeight(30);
    emeraudeCurrentPlayer->setStyleSheet("background-color : green");
    inventaireCurrentPlayerLayout->addWidget(emeraudeCurrentPlayer);
    saphirCurrentPlayer=new QLCDNumber;
    saphirCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(1)));
    saphirCurrentPlayer->setFixedHeight(30);
    saphirCurrentPlayer->setStyleSheet("background-color : blue");
    inventaireCurrentPlayerLayout->addWidget(saphirCurrentPlayer);
    rubisCurrentPlayer=new QLCDNumber;
    rubisCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(2)));
    rubisCurrentPlayer->setFixedHeight(30);
    rubisCurrentPlayer->setStyleSheet("background-color : red");
    inventaireCurrentPlayerLayout->addWidget(rubisCurrentPlayer);
    diamantCurrentPlayer=new QLCDNumber;
    diamantCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(3)));
    diamantCurrentPlayer->setFixedHeight(30);
    diamantCurrentPlayer->setStyleSheet("background-color : white");
    inventaireCurrentPlayerLayout->addWidget(diamantCurrentPlayer);
    onyxCurrentPlayer=new QLCDNumber;
    onyxCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(4)));
    onyxCurrentPlayer->setFixedHeight(30);
    onyxCurrentPlayer->setStyleSheet("background-color : gray");
    inventaireCurrentPlayerLayout->addWidget(onyxCurrentPlayer);
    jokerCurrentPlayer=new QLCDNumber;
    jokerCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(5)));
    jokerCurrentPlayer->setFixedHeight(30);
    jokerCurrentPlayer->setStyleSheet("background-color : gold");
    inventaireCurrentPlayerLayout->addWidget(jokerCurrentPlayer);

    //BONUS
    emeraudeCurrentBonusPlayer=new QLCDNumber;
    emeraudeCurrentBonusPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(0)));
    emeraudeCurrentBonusPlayer->setFixedHeight(30);
    emeraudeCurrentBonusPlayer->setStyleSheet("background-color : green");
    bonusCurrentPlayerLayout->addWidget(emeraudeCurrentBonusPlayer);
    saphirCurrentBonusPlayer=new QLCDNumber;
    saphirCurrentBonusPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(1)));
    saphirCurrentBonusPlayer->setFixedHeight(30);
    saphirCurrentBonusPlayer->setStyleSheet("background-color : blue");
    bonusCurrentPlayerLayout->addWidget(saphirCurrentBonusPlayer);
    rubisCurrentBonusPlayer=new QLCDNumber;
    rubisCurrentBonusPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(2)));
    rubisCurrentBonusPlayer->setFixedHeight(30);
    rubisCurrentBonusPlayer->setStyleSheet("background-color : red");
    bonusCurrentPlayerLayout->addWidget(rubisCurrentBonusPlayer);
    diamantCurrentBonusPlayer=new QLCDNumber;
    diamantCurrentBonusPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(3)));
    diamantCurrentBonusPlayer->setFixedHeight(30);
    diamantCurrentBonusPlayer->setStyleSheet("background-color : white");
    bonusCurrentPlayerLayout->addWidget(diamantCurrentBonusPlayer);
    onyxCurrentBonusPlayer=new QLCDNumber;
    onyxCurrentBonusPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(4)));
    onyxCurrentBonusPlayer->setFixedHeight(30);
    onyxCurrentBonusPlayer->setStyleSheet("background-color : black");
    bonusCurrentPlayerLayout->addWidget(onyxCurrentBonusPlayer);
///// END QLCD


    //PDV
    QGroupBox* pdvCurrentPlayerBox = new QGroupBox(tr("PDV"));
    QVBoxLayout* pdvCurrentPlayerLayout = new QVBoxLayout();
    pdvCurrentPlayer =new QLCDNumber();
    pdvCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getPDV()));
    pdvCurrentPlayer->setFixedHeight(30);
    pdvCurrentPlayerLayout->addWidget(pdvCurrentPlayer);
    pdvCurrentPlayerBox->setLayout(pdvCurrentPlayerLayout);

    //Reserve
    QGroupBox* reserveCurrentPlayerBox = new QGroupBox(tr("Reserve"));

    for(size_t i=0; i<3;i++)
        vuecartesReserve[i] = new VueCarte;
    for(size_t i=0; i<3;i++){
        layoutCartesReserve->addWidget(vuecartesReserve[i], 0, i);//ajout de la carte sur la grille
        //connect(vuecartesReserve[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
    }

    //Carte Reserve
    size_t k = 0;
    for(auto it: controleur.getJoueur(controleur.getCurrentPlayer()).getReserve()){
        if(k<3){
            vuecartesReserve[k]->setCarte(*it);
        }
        k++;
    }

    reserveCurrentPlayerBox->setLayout(layoutCartesReserve);

    //Boutons de controle de tour
    QGroupBox* playerActionBox = new QGroupBox(tr("Actions"));
    QVBoxLayout* playerActionLayout = new QVBoxLayout();

    QPushButton* endTurnBouton = new QPushButton("Terminer tour", this);
    QPushButton* cancelTurnBouton = new QPushButton("Annuler action", this);

    playerActionLayout->addWidget(endTurnBouton);
    playerActionLayout->addWidget(cancelTurnBouton);

    playerActionBox->setLayout(playerActionLayout);

    //Fin des boutons de controle de tour

    // STATS DE TOUS LES JOUEURS
    QString str;
    QHBoxLayout *playerBox = new QHBoxLayout;
    QGroupBox *playersDataBox = new QGroupBox();
    playersDataBox->setStyleSheet("QGroupBox {""padding: 1 1 1 1;} ");
    playersData = new QLabel();

    inventaireCurrentPlayerBox->setLayout(inventaireCurrentPlayerLayout);
    bonusCurrentPlayerBox->setLayout(bonusCurrentPlayerLayout);

    currentPlayerRessourceLayout->addWidget(inventaireCurrentPlayerBox);
    currentPlayerRessourceLayout->addWidget(bonusCurrentPlayerBox);

    currentPlayerRessourceBox->setLayout(currentPlayerRessourceLayout);
    currentPlayerLayout->addWidget(currentPlayerRessourceBox);
    currentPlayerLayout->addWidget(pdvCurrentPlayerBox);
    currentPlayerLayout->addWidget(reserveCurrentPlayerBox);

    currentPlayerLayout->addWidget(playerActionBox);

    currentPlayerBox->setLayout(currentPlayerLayout);
    playerLayout->addWidget(currentPlayerBox);


    for (int i = 0; i < controleur.getNbJoueurs(); ++i){

        str += "id :" + QString::number(controleur.getJoueur(i).getId()) + "   ";
        str += QString::fromStdString(controleur.getJoueur(i).getNom()) + "   ";
        str += "PDV:" + QString::number(controleur.getJoueur(i).getPDV()) + "   ";

        str += "Inventaire: [";
        for (size_t j = 0; j < 5; j++) {
            str += QString::number(controleur.getJoueur(i).getInventaire()[j]) + ",";
        }
        str += QString::number(controleur.getJoueur(i).getInventaire()[5]) + "]   ";

        str += "Bonus: [";
        for (size_t j = 0; j < 4; j++) {
            str += QString::number(controleur.getJoueur(i).getBonus()[j]) + ",";
        }
        str += QString::number(controleur.getJoueur(i).getInventaire()[4]) + "]   ";

        if (i != controleur.getNbJoueurs() - 1){
            str += "\n";
        }

        playersData->setText(str);


        //Manque affichage des cartes Reserve et CarteRemportées ? (pas besoin carteRemporté?)
        //controleur.getJoueur(i).getReserve();
        //controleur.getJoueur(i).getCartesRemportees();
    }

    playerBox->addWidget(playersData);
    playersDataBox->setLayout(playerBox);
    playerLayout->addWidget(playersDataBox);

    couche->addLayout(layoutInformations);
    couche->addLayout(layoutCartes);

    //affiche juste CarteNobles :
    couche->addWidget(carteNobles);
    couche->addLayout(layoutCartesNobles);
    couche->addLayout(playerLayout);
    setLayout(couche);


    //Gestion des Slots des boutons :
    connect(emeraudeBouton, &QPushButton::released, this, &VuePartie::emeraudeBoutonClique);
    connect(saphirBouton, &QPushButton::released, this, &VuePartie::saphirBoutonClique);
    connect(rubisBouton, &QPushButton::released, this, &VuePartie::rubisBoutonClique);
    connect(diamantBouton, &QPushButton::released, this, &VuePartie::diamantBoutonClique);
    connect(onyxBouton, &QPushButton::released, this, &VuePartie::onyxBoutonClique);

    connect(pioche1Bouton, &QPushButton::released, this, &VuePartie::pioche1BoutonClique);
    connect(pioche2Bouton, &QPushButton::released, this, &VuePartie::pioche2BoutonClique);
    connect(pioche3Bouton, &QPushButton::released, this, &VuePartie::pioche3BoutonClique);
    connect(cancelTurnBouton, &QPushButton::released, this, &VuePartie::cancelTurnClique);
    connect(endTurnBouton, &QPushButton::released, this, &VuePartie::endTurnClique);
}

void VuePartie::cancelTurnClique() {
    std::cout << "Action cancelled" << std::endl;
    nbJetonsPris = 0;
    cartePrise = false;
    sameJetonPris = false;
    for (size_t i = 0; i < 5; i++){
        int x = jetonsPris[i];
        for(size_t k = 0; k < x; k++) {
            controleur.rendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()),i);
        }
        jetonsPris[i] = 0;
    }
    selectionCarte = nullptr;
    for (size_t i=0; i<12; i++) {
        vuecartes[i]->setChecked(false);
    }
    updateJoueurInfo();
    updatePlateauInfo();
}

void VuePartie::endTurnClique() {
    std::cout << "Fin du tour" << std::endl;

    //fonctionne mais crash si pas assez de ressource :
    if(selectionCarte != nullptr && nbJetonsPris == 0)
        controleur.selectCarte(controleur.getJoueur(controleur.getCurrentPlayer()), *selectionCarte);

    //Clear local var
    for(size_t i = 0; i < 5; i++)
        jetonsPris[i] = 0;
    nbJetonsPris = 0;
    sameJetonPris = false;
    cartePrise = false;
    selectionCarte = nullptr;
    for (size_t i=0; i<12; i++) {
        vuecartes[i]->setChecked(false);
    }
    controleur.nextPlayer();
    updateJoueurInfo();
    updatePlateauInfo();
}

void VuePartie::emeraudeBoutonClique(){
   if ( ((nbJetonsPris == 1 && jetonsPris[0] == 1 && controleur.getPlateau().getBanque(0) >= 3) || (nbJetonsPris <= 2 && jetonsPris[0] == 0 && sameJetonPris == false)) && !cartePrise && controleur.getPlateau().getBanque(0) != 0 ){
       nbJetonsPris++;
       jetonsPris[0]++;
       if (jetonsPris[0] == 2)
           sameJetonPris = true;
       controleur.prendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()), 0);
       updateJoueurInfo();
       updatePlateauInfo();
   }
}

void VuePartie::saphirBoutonClique(){
    if ( ((nbJetonsPris == 1 && jetonsPris[1] == 1 && controleur.getPlateau().getBanque(1) >= 3 ) || (nbJetonsPris <= 2 && jetonsPris[1] == 0 && sameJetonPris == false)) && !cartePrise && controleur.getPlateau().getBanque(1) != 0){
        nbJetonsPris++;
        jetonsPris[1]++;
        if (jetonsPris[1] == 2)
            sameJetonPris = true;

        controleur.prendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()), 1);
        updateJoueurInfo();
        updatePlateauInfo();
    }
}

void VuePartie::rubisBoutonClique(){
    if ( ((nbJetonsPris == 1 && jetonsPris[2] == 1 && controleur.getPlateau().getBanque(2) >= 3) || (nbJetonsPris <= 2 && jetonsPris[2] == 0 && sameJetonPris == false)) && !cartePrise && controleur.getPlateau().getBanque(2) != 0){
        nbJetonsPris++;
        jetonsPris[2]++;
        if (jetonsPris[2] == 2)
            sameJetonPris = true;

        controleur.prendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()), 2);
        updateJoueurInfo();
        updatePlateauInfo();
    }
}

void VuePartie::diamantBoutonClique(){
    if ( ((nbJetonsPris == 1 && jetonsPris[3] == 1 && controleur.getPlateau().getBanque(3) >= 3) || (nbJetonsPris <= 2 && jetonsPris[3] == 0  && sameJetonPris == false)) && !cartePrise && controleur.getPlateau().getBanque(3) != 0 ){
        nbJetonsPris++;
        jetonsPris[3]++;
        if (jetonsPris[3] == 2)
            sameJetonPris = true;

        controleur.prendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()), 3);
        updateJoueurInfo();
        updatePlateauInfo();
    }
}

void VuePartie::onyxBoutonClique(){
    if ( ((nbJetonsPris == 1 && jetonsPris[4] == 1 && controleur.getPlateau().getBanque(4) >= 3) || (nbJetonsPris <= 2 && jetonsPris[4] == 0 && sameJetonPris == false)) && !cartePrise && controleur.getPlateau().getBanque(4) != 0){
        nbJetonsPris++;
        jetonsPris[4]++;
        if (jetonsPris[4] == 2)
            sameJetonPris = true;

        controleur.prendreRessource(controleur.getJoueur(controleur.getCurrentPlayer()), 4);
        updateJoueurInfo();
        updatePlateauInfo();
    }
}

void VuePartie::pioche1BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 1 !"); };
void VuePartie::pioche2BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 2 !"); };
void VuePartie::pioche3BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 3 !"); };

void VuePartie::carteClique(VueCarte* vc){
    if ( (nbJetonsPris==0 && !cartePrise) &&
         ((vc->getCarte().canBeBougth(controleur.getJoueur(controleur.getCurrentPlayer())) && controleur.getJoueur(controleur.getCurrentPlayer()).getReserve().size() >= 3 )
          || controleur.getJoueur(controleur.getCurrentPlayer()).getReserve().size() < 3 )) {
        if(vc->isChecked()){
            //Si il n'y a pas déjà des jetons de pris
            cartePrise = true;
            selectionCarte = &vc->getCarte();
            std::cout << "Il prend la carte !" << std::endl;
            //Suite du traitement dans le endTOUR
        }
    } else {
        if(!vc->isChecked()){
            vc->setChecked(false);
            cartePrise = false;
            selectionCarte = nullptr;
         } else {
            for (size_t i=0; i<12; i++) {
                vuecartes[i]->setChecked(false);
            }
            if(nbJetonsPris==0  &&
                    ((vc->getCarte().canBeBougth(controleur.getJoueur(controleur.getCurrentPlayer())) && controleur.getJoueur(controleur.getCurrentPlayer()).getReserve().size() >= 3 )
                     || controleur.getJoueur(controleur.getCurrentPlayer()).getReserve().size() < 3 ) ){
                cartePrise = true;
                vc->setChecked(true);
                std::cout << "Il prend la carte !" << std::endl;
                selectionCarte = &vc->getCarte();
            }
        }
    }
    return;
}

void VuePartie::carteNobleClique(VueCarte* vc){
    for (size_t i=0; i<controleur.getNbJoueurs() + 1; i++) {
        vuecartesNobles[i]->setChecked(false);
    }
}

void VuePartie::updateJoueurInfo() {
    emeraudeCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(0));
    saphirCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(1));
    rubisCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(2));
    diamantCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(3));
    onyxCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(4));
    jokerCurrentPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getInventaire(5));

    emeraudeCurrentBonusPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(0));
    saphirCurrentBonusPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(1));
    rubisCurrentBonusPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(2));
    diamantCurrentBonusPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(3));
    onyxCurrentBonusPlayer->display((int)controleur.getJoueur(controleur.getCurrentPlayer()).getBonus(4));

    pdvCurrentPlayer->display(QString::number(controleur.getJoueur(controleur.getCurrentPlayer()).getPDV()));

    for(size_t i=0; i<3; i++){
        vuecartesReserve[i]->setNoCarte();
    }

    size_t k = 0;
    for(auto it: controleur.getJoueur(controleur.getCurrentPlayer()).getReserve()){ //TODO:: à update
        if(k<3){
            vuecartesReserve[k]->setCarte(*it);
        }
        k++;
    }

    currentPlayerBox->setTitle(QString::fromStdString(controleur.getJoueur(controleur.getCurrentPlayer()).getNom()));

     QString str;
     for (int i = 0; i < controleur.getNbJoueurs(); ++i) {

         str += "id :" + QString::number(controleur.getJoueur(i).getId()) + "   ";
         str += QString::fromStdString(controleur.getJoueur(i).getNom()) + "   ";
         str += "PDV:" + QString::number(controleur.getJoueur(i).getPDV()) + "   ";

         str += "Inventaire: [";
         for (size_t j = 0; j < 5; j++) {
             str += QString::number(controleur.getJoueur(i).getInventaire()[j]) + ",";
         }
         str += QString::number(controleur.getJoueur(i).getInventaire()[5]) + "]   ";

         str += "Bonus: [";
         for (size_t j = 0; j < 4; j++) {
             str += QString::number(controleur.getJoueur(i).getBonus()[j]) + ",";
         }
         str += QString::number(controleur.getJoueur(i).getInventaire()[4]) + "]   ";

         if (i != controleur.getNbJoueurs() - 1){
             str += "\n";
         }

         playersData->setText(str);
    }

}

void VuePartie::updatePlateauInfo(){
    emeraudeBanque->display(controleur.getPlateau().getBanque(0));
    saphirBanque->display(controleur.getPlateau().getBanque(1));
    rubisBanque->display(controleur.getPlateau().getBanque(2));
    diamantBanque->display(controleur.getPlateau().getBanque(3));
    onyxBanque->display(controleur.getPlateau().getBanque(4));
    jokerBanque->display(controleur.getPlateau().getBanque(5));

}




