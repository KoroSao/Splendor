#ifndef VUEPLAYERCONFIG_H
#define VUEPLAYERCONFIG_H


#include <QSpinBox>
#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include<stdlib.h>
#include <QLineEdit>
#include <QString>
#include <QInputDialog>
#include <iostream>
#include "./src/controleur/controleur.h"
#include "./src/partie/vuePartie.h"


class vuePlayerConfig : public QWidget
{
    Q_OBJECT
private:
    int choix;
    int nbJoueurs;
    std::vector<QHBoxLayout*> iahumain;
    std::vector<string> noms;
    std::vector<string> types;
    QPushButton*  bouton;
    QHBoxLayout* layout;
    QLabel* sentence;
    QComboBox* choixtype;
    QVBoxLayout* layoutPrinc;
    QLineEdit* name;

private slots :
    void suivant();

public:
    explicit vuePlayerConfig(int choix, int nbJoueurs, QWidget* parent = nullptr);
    virtual ~vuePlayerConfig();

};

#endif // VUEPLAYERCONFIG_H
