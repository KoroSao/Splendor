#include <QLabel>
//#include <QlineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "./vueCarte.h"
#include "../type/type.h"
#include <QPainter>
#include <QString>
#include <QStaticText>

VueCarte::VueCarte(const Splendor::Carte& c, QWidget *parent) : QPushButton(parent),carte(&c)
{
    //setStyleSheet("background-color : blue");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(60,100);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);

}

VueCarte::VueCarte(QWidget *parent): QPushButton(parent)
{

    //setBackgroundRole(QPalette::AlternateBase);
    setStyleSheet("background-color : yellow");
    setAutoFillBackground(true);
    setFixedSize(60,100);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(false);
}

void VueCarte::paintEvent(QPaintEvent * /* event */)
{

    QPainter painter(this);

    // rectangle autour de la carte
    pen.setColor(QColor("gray"));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    brush.setStyle(Qt::SolidPattern);

    //changement de couleur de fond pour une carte selectionné
    if (isChecked()) brush.setColor("gold");
    else brush.setColor(QColor("#CF8532"));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(QRect(2, 2, width() - 2, height() - 2));

    //suppression de la brush
    brush.setStyle(Qt::NoBrush);
    painter.setBrush(brush);

    if (carte==nullptr) { // si la vue de carte n'a pas de carte on affiche un message
        painter.drawText(QRect(7,25,50,30), Qt::AlignCenter, tr("VIDE"));
        return;
    }

    else{

        //on affiche les infos en fonction du type de carte
        QString infos = "";
        const Splendor::CarteDeveloppement* c = dynamic_cast<const Splendor::CarteDeveloppement*>(carte);
        if (c){
            infos = tr(Splendor::toString(c->getType()).c_str());
            infos+= "\nPDV : ";
            infos+= to_string(c->getPDV()).c_str();
            infos += "\n";
            for (size_t i =0;i<5;i++){//Une carte ne produit qu'une seul ressource
                if(c->getBonus(i) != 0) infos+=Splendor::ressources_name[i].c_str();
             }

        }
        const Splendor::CarteNoble* c_n = dynamic_cast<const Splendor::CarteNoble*>(carte);
        if(c_n){
            infos+="Noble\n";
            infos+= "\nPDV : ";
            infos+= to_string(c_n->getPDV()).c_str();
        }
        pen.setColor(QColor("black"));
        painter.setPen(pen);
        painter.drawText(QRect(7,25,50,50), Qt::AlignCenter, infos);


        //on affiche le couts de la carte
        size_t nb_cout = 0;
        vector<std::string> couleur_ressources = {"green", "blue", "red", "white", "black"};
        for (size_t i = 0; i <5; i++){
            if (carte->getCouts(i) != 0){
                pen.setColor(QColor(couleur_ressources[i].c_str()));
                painter.setPen(pen);
                painter.drawRect(QRect(2+nb_cout*12, 2, 10, 20));
                pen.setColor(QColor("black"));
                painter.setPen(pen);
                painter.drawText(QRect(2+nb_cout*12, 2, 10, 20), Qt::AlignCenter, to_string(carte->getCouts(i)).c_str());
                nb_cout ++;

            }
        }

        }

}
