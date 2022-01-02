/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Call
*/

#ifndef CALL_HPP_
#define CALL_HPP_

#include "App.h"
#include "ModifyPopup.h"
#include "ContactLabel.h"

class Call : public QWidget {
    Q_OBJECT
    public:
        enum Scene {NOCALL, ONCALL, RECEIVECALL};
        Call(QWidget *parent = 0);

        void setScene(Scene, std::string user);
        QStackedLayout *getLayout() const { return this->scene;};
        Scene getScene() const {return static_cast<Scene>(scene->currentIndex());};
        void updateCall();
    public slots:
        void takeCall();
        void refuseCall();
        void hangup();
        void addToCall();
        void removeFromCall();
    protected:
    private:
        App *app;
        QString contextCall = "";
        QLabel *receiveCallName;
        QStackedLayout *scene = new QStackedLayout;
        QGridLayout *onCallLayout = new QGridLayout;
        QGridLayout *receiveCallLayout = new QGridLayout;
        QVBoxLayout *contactList = new QVBoxLayout;
        QVBoxLayout *buttonList = new QVBoxLayout;
        QWidget *onCall = new QWidget;
        QWidget *receiveCall = new QWidget;

        ModifyPopup *dialog = new ModifyPopup;
};

#endif /* !CALL_HPP_ */
