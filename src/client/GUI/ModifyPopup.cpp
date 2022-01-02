/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/


#include <QtGui>
#include "ModifyPopup.h"

ModifyPopup::ModifyPopup(QWidget *parent)
        : QDialog(parent)
{
    QLabel *nameLabel = new QLabel(tr("Enter the name of a contact:"));
    lineEdit = new QLineEdit;

    findButton = new QPushButton(tr("&Find"));

    QVBoxLayout *mainlayout = new QVBoxLayout;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(nameLabel);
    layout->addWidget(lineEdit);

    mainlayout->addLayout(layout);
    mainlayout->addWidget(findButton);
    setLayout(mainlayout);
    setWindowTitle(tr("Add a Contact"));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
}

void ModifyPopup::findClicked()
{
    QString text = lineEdit->text();

    if (text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Please enter a name."));
    } else {
        user = text.toStdString();
        lineEdit->clear();
        hide();
        accept();
    }
}

std::string ModifyPopup::getUserAdded()
{
    return user;
}