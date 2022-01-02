/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Login
*/

#ifndef LOGIN_HPP_
#define LOGIN_HPP_

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QGridLayout>
#include <QtWidgets>
#include <QWidget>
#include "App.h"

class Login : public QWidget{
    Q_OBJECT

    public:
        Login(QWidget *parent);
        ~Login();

        void update();
    protected:
    public slots:
        void proceed_login();
        void reconnect();
    private:
        QLineEdit *username_edit;
        QLineEdit *password_edit;
        QLabel *username_info;
        QLabel *password_info;
        QLabel *username_error;
        QLabel *password_error;
        QPushButton *login_button;
        QPushButton *reconnect_button;

        QGridLayout *login_layout;

        App *parent;
};

#endif /* !LOGIN_HPP_ */
