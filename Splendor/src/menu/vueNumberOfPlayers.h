#ifndef VUENUMBEROFPLAYERS_H
#define VUENUMBEROFPLAYERS_H

#include <QSpinBox>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <string>


class vueNumberOfPlayers : public QWidget
{
    Q_OBJECT

    QVBoxLayout* spinBoxLayout;
    QVBoxLayout* choiceLayout;
    QLabel* integerLabel;
    QLabel* phrase;
    QSpinBox* integerSpinBox;
    QComboBox* choixjeu;
    QVBoxLayout* layoutPrincipal;
    QPushButton*  bouton;

private slots :
    void suivant();

public:
    explicit vueNumberOfPlayers(QWidget* parent = nullptr);

};


#endif // VUENUMBEROFPLAYERS_H
