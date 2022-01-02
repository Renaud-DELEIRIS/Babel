/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#ifndef BABEL_MODIFYPOPUP_H
#define BABEL_MODIFYPOPUP_H

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "include/common/User.hpp"


class ModifyPopup : public QDialog
{

    Q_OBJECT
    public:
        ModifyPopup(QWidget *parent = 0);
        std::string getUserAdded();

    public slots:
        void findClicked();

    private:
        QPushButton *findButton;
        QLineEdit *lineEdit;
        std::string user = "";
};


#endif //BABEL_MODIFYPOPUP_H
