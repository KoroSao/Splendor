#include "vuepioche.h"
#include <QPainter>

VuePioche::VuePioche(QWidget *parent): QPushButton(parent), pioche(nullptr)
{

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(60,100);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);
}



VuePioche::VuePioche(Splendor::Pioche& p, QWidget *parent): QPushButton(parent), pioche(&p)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(60,100);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    setCheckable(true);
}


void VuePioche::paintEvent(QPaintEvent * /*event */)
{
    QPainter painter(this);

    // rectangle autour de la pioche
    QColor contour_pioche(43, 14, 0);
    pen.setColor(contour_pioche);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    brush.setStyle(Qt::SolidPattern);

    //changement de couleur de fond pour une pioche selectionné
    QColor fond_pioche(93, 31, 0);
    if (isChecked()) brush.setColor(fond_pioche.lighter(150));
    else brush.setColor(fond_pioche);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(QRect(2, 2, width() - 2, height() - 2));

    //suppression de la brush
    brush.setStyle(Qt::NoBrush);
    painter.setBrush(brush);

    //on affiche les infos en fonction du type de carte
    QString infos = "Pioche\nNiveau ";
    infos += Splendor::toString(pioche->getType()).c_str();
    pen.setColor(QColor("black"));
    painter.setPen(pen);
    painter.drawText(QRect(7,25,50,50), Qt::AlignCenter, infos);
}
