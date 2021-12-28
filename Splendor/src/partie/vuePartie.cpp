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
//#include "vuecarte.h"

VuePartie::VuePartie(QWidget *parent) : QWidget(parent), vuecartes(20,nullptr), vuecartesNobles(5,nullptr), vuecartesReserve(3,nullptr)
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

    //Gestion des Slots des boutons :
    connect(emeraudeBouton, &QPushButton::released, this, &VuePartie::emeraudeBoutonClique);
    connect(saphirBouton, &QPushButton::released, this, &VuePartie::saphirBoutonClique);
    connect(rubisBouton, &QPushButton::released, this, &VuePartie::rubisBoutonClique);
    connect(diamantBouton, &QPushButton::released, this, &VuePartie::diamantBoutonClique);
    connect(onyxBouton, &QPushButton::released, this, &VuePartie::onyxBoutonClique);

    connect(pioche1Bouton, &QPushButton::released, this, &VuePartie::pioche1BoutonClique);
    connect(pioche2Bouton, &QPushButton::released, this, &VuePartie::pioche2BoutonClique);
    connect(pioche3Bouton, &QPushButton::released, this, &VuePartie::pioche3BoutonClique);

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
        connect(vuecartesNobles[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
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

    /*
    QGroupBox* currentPlayerBox();
    QHBoxLayout* currentPlayerLayout;
    QGroupBox* currentPlayerRessourceBox;
    QVBoxLayout* currentPlayerRessourceLayout;
    QGroupBox* inventaireCurrentPlayerBox();
    QGroupBox* bonusCurrentPlayerBox();
    QGroupBox* pdvCurrentPlayerBox();
    QGroupBox* reserveCurrentPlayerBox();


    */

    QGroupBox *currentPlayerBox = new QGroupBox(tr("Current Player : player xx")); //TODO:: add name current player
    QHBoxLayout* currentPlayerLayout = new QHBoxLayout();
    QGroupBox* currentPlayerRessourceBox = new QGroupBox();
    QVBoxLayout* currentPlayerRessourceLayout = new QVBoxLayout();

    QGroupBox* inventaireCurrentPlayerBox = new QGroupBox(tr("inventaire"));
    QGroupBox* bonusCurrentPlayerBox = new QGroupBox(tr("bonus"));

    QHBoxLayout *inventaireCurrentPlayerLayout = new QHBoxLayout;
    QHBoxLayout *bonusCurrentPlayerLayout = new QHBoxLayout;
////// START QLCD
    emeraudeCurrentPlayer=new QLCDNumber;
    emeraudeCurrentPlayer->display(QString::number(0));
    emeraudeCurrentPlayer->setFixedHeight(30);
    emeraudeCurrentPlayer->setStyleSheet("background-color : green");
    inventaireCurrentPlayerLayout->addWidget(emeraudeCurrentPlayer);
    saphirCurrentPlayer=new QLCDNumber;
    saphirCurrentPlayer->display(QString::number(0));
    saphirCurrentPlayer->setFixedHeight(30);
    saphirCurrentPlayer->setStyleSheet("background-color : blue");
    inventaireCurrentPlayerLayout->addWidget(saphirCurrentPlayer);
    rubisCurrentPlayer=new QLCDNumber;
    rubisCurrentPlayer->display(QString::number(0));
    rubisCurrentPlayer->setFixedHeight(30);
    rubisCurrentPlayer->setStyleSheet("background-color : red");
    inventaireCurrentPlayerLayout->addWidget(rubisCurrentPlayer);
    diamantCurrentPlayer=new QLCDNumber;
    diamantCurrentPlayer->display(QString::number(0));
    diamantCurrentPlayer->setFixedHeight(30);
    diamantCurrentPlayer->setStyleSheet("background-color : white");
    inventaireCurrentPlayerLayout->addWidget(diamantCurrentPlayer);
    onyxCurrentPlayer=new QLCDNumber;
    onyxCurrentPlayer->display(QString::number(0));
    onyxCurrentPlayer->setFixedHeight(30);
    onyxCurrentPlayer->setStyleSheet("background-color : gray");
    inventaireCurrentPlayerLayout->addWidget(onyxCurrentPlayer);
    jokerCurrentPlayer=new QLCDNumber;
    jokerCurrentPlayer->display(QString::number(0));
    jokerCurrentPlayer->setFixedHeight(30);
    jokerCurrentPlayer->setStyleSheet("background-color : gold");
    inventaireCurrentPlayerLayout->addWidget(jokerCurrentPlayer);

    //BONUS
    emeraudeCurrentBonusPlayer=new QLCDNumber;
    emeraudeCurrentBonusPlayer->display(QString::number(0));
    emeraudeCurrentBonusPlayer->setFixedHeight(30);
    emeraudeCurrentBonusPlayer->setStyleSheet("background-color : green");
    bonusCurrentPlayerLayout->addWidget(emeraudeCurrentBonusPlayer);
    saphirCurrentBonusPlayer=new QLCDNumber;
    saphirCurrentBonusPlayer->display(QString::number(0));
    saphirCurrentBonusPlayer->setFixedHeight(30);
    saphirCurrentBonusPlayer->setStyleSheet("background-color : blue");
    bonusCurrentPlayerLayout->addWidget(saphirCurrentBonusPlayer);
    rubisCurrentBonusPlayer=new QLCDNumber;
    rubisCurrentBonusPlayer->display(QString::number(0));
    rubisCurrentBonusPlayer->setFixedHeight(30);
    rubisCurrentBonusPlayer->setStyleSheet("background-color : red");
    bonusCurrentPlayerLayout->addWidget(rubisCurrentBonusPlayer);
    diamantCurrentBonusPlayer=new QLCDNumber;
    diamantCurrentBonusPlayer->display(QString::number(0));
    diamantCurrentBonusPlayer->setFixedHeight(30);
    diamantCurrentBonusPlayer->setStyleSheet("background-color : white");
    bonusCurrentPlayerLayout->addWidget(diamantCurrentBonusPlayer);
    onyxCurrentBonusPlayer=new QLCDNumber;
    onyxCurrentBonusPlayer->display(QString::number(0));
    onyxCurrentBonusPlayer->setFixedHeight(30);
    onyxCurrentBonusPlayer->setStyleSheet("background-color : black");
    bonusCurrentPlayerLayout->addWidget(onyxCurrentBonusPlayer);
///// END QLCD

    //PDV
    QGroupBox* pdvCurrentPlayerBox = new QGroupBox(tr("PDV"));
    QHBoxLayout* pdvCurrentPlayerLayout = new QHBoxLayout();
    pdvCurrentPlayer=new QLCDNumber;
    pdvCurrentPlayer->display(QString::number(10));
    pdvCurrentPlayer->setFixedHeight(30);
    pdvCurrentPlayerLayout->addWidget(pdvCurrentPlayer);
    pdvCurrentPlayerBox->setLayout(pdvCurrentPlayerLayout);

    //Reserve
    QGroupBox* reserveCurrentPlayerBox = new QGroupBox(tr("reserve"));



    for(size_t i=0; i<3;i++)
        vuecartesReserve[i] = new VueCarte;
    for(size_t i=0; i<3;i++){
        layoutCartesReserve->addWidget(vuecartesReserve[i], 0, i);//ajout de la carte sur la grille
        connect(vuecartesReserve[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
    }

    //Carte Nobles test pour reserve
    size_t k = 0;
    for(auto it: controleur.getPlateau().getNiveauNobles().getCartes()){ //TODO:: à update
        if(k<3){
            vuecartesReserve[k]->setCarte(*it);
        }
        k++;
    }

    reserveCurrentPlayerBox->setLayout(layoutCartesReserve);

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
        playerBox->addWidget(playersData);
        playersDataBox->setLayout(playerBox);


        //Manque affichage des cartes Reserve et CarteRemportées ? (pas besoin carteRemporté?)
        //controleur.getJoueur(i).getReserve();
        //controleur.getJoueur(i).getCartesRemportees();
    }


    playerLayout->addWidget(playersDataBox);

    couche->addLayout(layoutInformations);
    couche->addLayout(layoutCartes);

    //affiche juste CarteNobles :
    couche->addWidget(carteNobles);
    couche->addLayout(layoutCartesNobles);
    couche->addLayout(playerLayout);
    setLayout(couche);
}

void VuePartie::emeraudeBoutonClique(){
    //emeraudeBouton->setText("click!");
    qInfo("L'utilisateur x souhaite prendre un jeton émeraude !");
};
void VuePartie::saphirBoutonClique(){ qInfo("L'utilisateur x souhaite prendre un jeton saphir !"); };
void VuePartie::rubisBoutonClique(){ qInfo("L'utilisateur x souhaite prendre un jeton rubis !"); };
void VuePartie::diamantBoutonClique(){ qInfo("L'utilisateur x souhaite prendre un jeton diamant !"); };
void VuePartie::onyxBoutonClique(){ qInfo("L'utilisateur x souhaite prendre un jeton onyx !"); };

void VuePartie::pioche1BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 1 !"); };
void VuePartie::pioche2BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 2 !"); };
void VuePartie::pioche3BoutonClique(){ qInfo("L'utilisateur x souhaite réserver une carte dans la pioche numéro 3 !"); };

void VuePartie::carteClique(VueCarte* vc){
   return;
}

//void VuePartie::carteClique(VueCarte* vc){
//    if(!vc->cartePresente()){
//        //qDebug("ajouter carte !\n");
//        if(controleur.getPioche().estVide()/*.getNbCartes() == 0*/){
//            QMessageBox message(QMessageBox::Icon::Warning, "Attention", "La pioche est vide");
//            message.exec();
//        }
//        controleur.distribuer(); //ajout d'une carte
//        //mise à jour des affectations des cartes aux vues des cartes
//        size_t i = 0;
//        for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
//            vuecartes[i]->setCarte(*it);
//            i++;
//        }
//        nbCartesPioche->setValue(controleur.getPioche().getNbCartes());
//    } else {
//        if(vc->isChecked()){ //une nouvelle carte a été selectionnée
//            selectionCartes.insert(&vc->getCarte()); //on insere la carte dans l'ensemble des cartes sélectionnées

//            if(selectionCartes.size() == 3){ //on a une combinaison qui peut être un SET
//                //on crée et teste une combinaison
//                vector<const Set::Carte*> c(selectionCartes.begin() , selectionCartes.end());
//                Set::Combinaison comb(*c[0], *c[1], *c[2]);

//                if(comb.estUnSET()){ //c'est un SET ! Il faut mettre à jour le plateau
//                    //Retirer les cartes du plateau
//                    controleur.getPlateau().retirer(*c[0]);
//                    controleur.getPlateau().retirer(*c[1]);
//                    controleur.getPlateau()..retirer(*c[2]);
//                    selectionCartes.clear(); //il n'y a plus de cartes sélectionnées

//                    //s'il n'y a pas au moins 12 cartes sur le plateau, on le complète
//                    if(controleur.getPlateau().getNbCartes() < 12){
//                        controleur.distribuer();
//                    }
//                    //mise à jour du score
//                    scoreValue++;
//                    scoreJoueur->display(scoreValue);
//                    //mise à jour de la vue du plateau
//                    //-> nettoyage du plateau et mise à jour de la vue des cartes
//                    for (size_t i=0; i<vuecartes.size(); i++) {
//                        vuecartes[i]->setNoCarte();
//                    }

//                    size_t i = 0;
//                    for(auto it=controleur.getPlateau().begin();it!=controleur.getPlateau().end();++it){
//                        vuecartes[i]->setCarte(*it);
//                        i++;
//                    }

//                    //mise à jour de la vue de la pioche
//                    nbCartesPioche->setValue(controleur.getPioche().getNbCartes());

//                } else {
//                    QMessageBox message(QMessageBox::Icon::Warning, "Attention", "Ce n'est pas un set");
//                    message.exec();
//                    //déselection des cartes
//                    for (size_t i=0; i<vuecartes.size(); i++) {
//                        vuecartes[i]->setChecked(false);
//                    }
//                    selectionCartes.clear(); //l'ensemble des cartes sélectionnées est vide
//                }
//            }

//        } else {
//            //la carte est désélectionnéee
//            selectionCartes.erase(&vc->getCarte());
//        }
//    }

//    update(); //mise à jour de la vue
//}


//#################################################################
//#################################################################
// //TODO: TO DELETE :
//#################################################################
//#################################################################




