#ifndef VUEPIOCHE_H
#define VUEPIOCHE_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <vector>
#include <set>
#include "../controleur/controleur.h"
#include <QPen>
#include <QBrush>
#include <QPushButton>


class VuePioche : public QPushButton
{
    Q_OBJECT
public:
    VuePioche(QWidget* parent = nullptr);
    VuePioche(Splendor::Pioche& p, QWidget *parent = nullptr);
    void setPioche(Splendor::Pioche& pioche) {this->pioche = &pioche;}
    Splendor::Pioche& getPioche() const{ return *pioche; }

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Splendor::Pioche* pioche;
    QPen pen;
    QBrush brush;
signals:
    // quand la vue de pioche est cliquée, elle émet un signal en transmettant son adresse
    void piocheClicked(VuePioche*);
public slots:
private slots:
    void clickedEvent() { emit piocheClicked(this); }
};


#endif // VUEPIOCHE_H
