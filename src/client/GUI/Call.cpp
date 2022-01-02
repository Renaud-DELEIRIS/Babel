/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Call
*/

#include "Call.h"
#include "UserMenu.h"

Call::Call(QWidget *parent)
{
    this->app = static_cast<App *>(parent);

    receiveCallName = new QLabel;
    QLabel *onCallName = new QLabel("On call");
    QPushButton *receiveCallAccept = new QPushButton("Answer");
    QPushButton *receiveCallDeny = new QPushButton("Deny");

    QPushButton *addToCallb = new QPushButton("Add");
    QPushButton *removeToCallb = new QPushButton("Remove");
    QPushButton *hangupb = new QPushButton("Hang Up");

    connect(receiveCallAccept, SIGNAL(clicked()), this, SLOT(takeCall()));
    connect(receiveCallDeny, SIGNAL(clicked()), this, SLOT(refuseCall()));
    connect(hangupb, SIGNAL(clicked()), this, SLOT(hangup()));
    connect(addToCallb, SIGNAL(clicked()), this, SLOT(addToCall()));
    connect(removeToCallb, SIGNAL(clicked()), this, SLOT(removeFromCall()));
    receiveCallLayout->addWidget(receiveCallName, 0, 0, 1, 2, Qt::AlignCenter);
    receiveCallLayout->addWidget(receiveCallAccept, 2, 0);
    receiveCallLayout->addWidget(receiveCallDeny, 2, 1);

    buttonList->addWidget(addToCallb);
    buttonList->addWidget(removeToCallb);
    buttonList->addWidget(hangupb);
    contactList->setAlignment(Qt::AlignTop);
    QHBoxLayout *row = new QHBoxLayout;
    row->addLayout(contactList);
    row->addStretch();
    row->addLayout(buttonList);
    onCallLayout->addWidget(onCallName, 0, 0, 1, 2, Qt::AlignCenter);
    onCallLayout->addLayout(row, 1, 0);

    onCall->setLayout(onCallLayout);
    receiveCall->setLayout(receiveCallLayout);

    scene->addWidget(new QWidget);
    scene->addWidget(onCall);
    scene->addWidget(receiveCall);
}

void Call::hangup()
{
    this->app->hangup();
    this->setScene(NOCALL, "");
}

void Call::setScene(Scene scene, std::string context)
{
    this->scene->setCurrentIndex(static_cast<int>(scene));
    this->contextCall = QString::fromStdString(context);
    if (scene == RECEIVECALL)
        receiveCallName->setText(QString::fromStdString("%1 is calling").arg(this->contextCall));
}

void Call::refuseCall()
{
    if (!this->app->getTcp()->isConnected()) {
        this->app->getUserMenu()->reconnectButton->show();
        return;
    }
    this->app->refuseCall();
    setScene(NOCALL, "");
}

void Call::takeCall()
{
    if (!this->app->getTcp()->isConnected()) {
        this->app->getUserMenu()->reconnectButton->show();
        return;
    }
    this->app->acceptCall();
    setScene(ONCALL, "");
}

void Call::addToCall()
{
    if (!this->app->getTcp()->isConnected()) {
        this->app->getUserMenu()->reconnectButton->show();
        return;
    }
    dialog->show();
    if (dialog->exec() == 1) {
        std::string contactName = dialog->getUserAdded();
        if (app->checkUser(contactName)) {
            UserApp user = app->getUser(contactName);
            app->addContactToCall(user);
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                                     tr("Sorry, canno't find \"%1\"")
                                     .arg(QString::fromStdString(contactName)));
            return;
        }
    }
}

void Call::removeFromCall()
{
    if (!this->app->getTcp()->isConnected()) {
        this->app->getUserMenu()->reconnectButton->show();
        return;
    }
    dialog->show();
    if (dialog->exec() == 1) {
        std::string contactName = dialog->getUserAdded();
        if (app->checkUser(contactName)) {
            UserApp user = app->getUser(contactName);
            app->removeContactToCall(user);
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                                     tr("Sorry, canno't find \"%1\"")
                                     .arg(QString::fromStdString(contactName)));
            return;
        }
    }
}

void Call::updateCall()
{
    QLayoutItem *wItem;
    while ((wItem = contactList->takeAt(0)) != 0)
        delete wItem;
    std::vector<UserApp> linkeds = app->getUserInCall();
    for (auto &contact : linkeds) {
        ContactLabel *label = new ContactLabel(contact);
        label->setText(QString::fromStdString(label->getUser().username));
        contactList->addWidget(label);
    }
}
