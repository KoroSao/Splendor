#ifndef VUECARTE_H
#define VUECARTE_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <vector>
#include <set>
#include "../controleur/controleur.h"
#include <QPen>
#include <QBrush>
#include <QPushButton>

class VueCarte : public QPushButton
{
    Q_OBJECT
public:
    VueCarte(const Splendor::Carte& c, QWidget *parent = nullptr);
    explicit VueCarte(QWidget *parent = nullptr);
    // affecter une nouvelle carte à la vue
    void setCarte(const Splendor::Carte& c) { setCheckable(true); setChecked(false); carte=&c; update(); }
    // vue sans carte
    void setNoCarte() { carte=nullptr; setCheckable(false); update(); }
    const Splendor::Carte& getCarte() const { return *carte; }
    bool cartePresente() const { return carte!=nullptr; }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const Splendor::Carte* carte=nullptr;
    QPen pen;
    QBrush brush;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueCarte*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};

#endif // VUECARTE_H
