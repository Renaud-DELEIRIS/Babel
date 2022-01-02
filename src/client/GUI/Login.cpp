/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Login
*/

#include "Login.h"
#include <iostream>

Login::Login(QWidget *parent)
{
    this->username_info = new QLabel("username:", this);
    this->username_info->setStyleSheet("color: #5f6368;");
    this->username_edit = new QLineEdit("", this);
    //SET MAX USERNAME LEN
    this->username_error = new QLabel("error username", this);
    this->username_error->setStyleSheet("font-weight: bold; color: red");
    this->username_error->hide();
    this->password_info = new QLabel("password:", this);
    this->password_info->setStyleSheet("color: #5f6368;");
    this->password_edit = new QLineEdit("", this);
    this->password_edit->setEchoMode(QLineEdit::Password);
    this->password_error = new QLabel("error password", this);
    this->password_error->setStyleSheet("font-weight: bold; color: red");
    this->password_error->hide();
    this->login_button = new QPushButton("LOGIN", this);
    this->reconnect_button = new QPushButton("reconnect", this);

    this->login_layout = new QGridLayout(this);
    login_layout->addWidget(this->username_info, 0, 0);
    login_layout->addWidget(this->username_edit, 1, 0);
    login_layout->addWidget(this->username_error, 2, 0);
    login_layout->addWidget(this->password_info, 4, 0);
    login_layout->addWidget(this->password_edit, 5, 0);
    login_layout->addWidget(this->password_error, 6, 0);
    login_layout->addWidget(this->login_button, 7, 0, 1, 2);
    login_layout->addWidget(reconnect_button, 8, 0, 1, 2);
    parent->setLayout(login_layout);
    connect(login_button, SIGNAL(clicked()), this, SLOT(proceed_login()));
    connect(reconnect_button, SIGNAL(clicked()), this, SLOT(reconnect()));
    this->parent = static_cast<App *>(parent);
    if (this->parent->getTcp()->isConnected())
        reconnect_button->hide();
}

Login::~Login()
{
    QLayoutItem *item;
    QWidget *widget;
    while ((item = login_layout->takeAt(0))) {
        if ((widget = item->widget()) != 0)
            widget->hide();
        delete item;
    }
    delete login_layout;
}

void Login::reconnect()
{
    this->parent->getTcp()->doConnect();
    if (this->parent->getTcp()->isConnected())
        this->reconnect_button->hide();
}

void Login::proceed_login()
{
    loginCode code;

    this->username_error->hide();
    this->password_error->hide();
    if (this->username_edit->text().isEmpty()) {
        this->username_error->setText("Username cannot be empty");
        this->username_error->show();
        return;
    }
    if (this->password_edit->text().isEmpty()) {
        this->password_error->setText("Password cannot be empty");
        this->password_error->show();
        return;
    }
    code = parent->login(this->username_edit->text().toStdString(), this->password_edit->text().toStdString());
    switch(code) {
        case BAD_PASSWORD:
            this->password_error->setText("Password not valid");
            this->password_error->show();
            break;
        case USER_NOT_EXIST:
            this->username_error->setText("Username not valid");
            this->username_error->show();
            break;
        case SUCCESS:
            parent->update();
            break;
        case NOT_CONNECTED:
            this->reconnect_button->show();
            break;
    }
}

void Login::update()
{
}
