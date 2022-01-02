/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include "UserMenu.h"
#include <iostream>

UserMenu::UserMenu(QWidget *parent)
{
    this->app = static_cast<App *>(parent);
    QLabel *nameLabel = new QLabel(this);
    nameLabel->setFrameStyle(QFrame::Panel);
    nameLabel->setText(QString::fromStdString(app->getContext().username));

    QLabel *addressLabel = new QLabel(tr("Contact:"));
    contactDraw = QList<ContactLabel *>();

    addButton = new QPushButton(tr("&Add"));

    removeButton = new QPushButton(tr("&Remove"));
    reconnectButton = new QPushButton(tr("&Reconnect"));
    reconnectButton->hide();
    removeButton->setEnabled(false);
    callButon = new QPushButton(tr("&Call"));
    callButon->setEnabled(false);

    dialog = new ModifyPopup;

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(callButon, SIGNAL(clicked()), this, SLOT(call()));
    connect(reconnectButton, SIGNAL(clicked()), this, SLOT(reconnect()));

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(callButon);
    buttonLayout1->addStretch();

    contactLayout = new QVBoxLayout;
    contactLayout->addWidget(addressLabel);

    callWidget = new Call(app);

    mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(reconnectButton, 0, 1);
    mainLayout->addLayout(contactLayout, 2, 0, Qt::AlignTop);
    mainLayout->addLayout(buttonLayout1, 2, 2);
    mainLayout->addLayout(callWidget->getLayout(), 0, 4, 3, 3);

    parent->setLayout(mainLayout);
    fetchContact();
}

void UserMenu::reconnect()
{
    this->app->getTcp()->doConnect();
    if (this->app->getTcp()->isConnected())
        this->reconnectButton->hide();
}

void UserMenu::fetchContact()
{
    if (!this->app->getTcp()->isConnected()) {
        this->reconnectButton->show();
        return;
    }
    for (auto a : contactDraw)
        delete a;
    this->contactDraw.clear();
    std::vector<UserApp> linkeds = app->fetchContact();
    for (auto contact : linkeds) {
        ContactLabel *label = new ContactLabel(contact);
        label->setText(QString::fromStdString("- " + contact.username));
        contactLayout->addWidget(label);
        connect(label, SIGNAL(clicked(UserApp)), this, SLOT(setSelectioned(UserApp)));
        contactDraw.push_back(label);
    }
}

ContactLabel *UserMenu::findLabelWithId(int id)
{
    for (auto label : contactDraw) {
        if (label->getUser().id == id) {
            return label;
        }
    }
    return NULL;
}

void UserMenu::setSelectioned(UserApp user)
{
    if (this->callWidget->getScene() != Call::Scene::NOCALL)
        return;
    this->selection = user;
    for (auto a : contactDraw)
        a->setFrameStyle(0);
    findLabelWithId(user.id)->setFrameStyle(QFrame::Box | QFrame::Plain);
    this->removeButton->setEnabled(true);
    this->callButon->setEnabled(true);
}

void UserMenu::addContact()
{
    if (!this->app->getTcp()->isConnected()) {
        this->reconnectButton->show();
        return;
    }
    if (this->callWidget->getScene() != Call::Scene::NOCALL)
        return;
    dialog->show();
    if (dialog->exec() == 1) {
        std::string contactName = dialog->getUserAdded();
        if (app->checkUser(contactName)) {
            if (app->addContact(contactName))
                fetchContact();
            else
                QMessageBox::information(this, tr("Contact Add Error"),
                                tr("Can't add \"%1\", already in your contact list")
                                .arg(QString::fromStdString(contactName)));
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                                     tr("Sorry, canno't find \"%1\"")
                                     .arg(QString::fromStdString(contactName)));
            return;
        }
    }
}

void UserMenu::removeContact()
{
    if (!this->app->getTcp()->isConnected()) {
        this->reconnectButton->show();
        return;
    }
    if (this->selection.id == -1)
        return;
    if (this->callWidget->getScene() != Call::Scene::NOCALL)
        return;
    int index = 0;
    for (auto label : contactDraw) {
        if (this->selection.id == label->getUser().id) {
            app->removeContact(label->getUser().username);
            delete label;
            contactDraw.erase(contactDraw.begin() + index);
            this->selection.id = -1;
            this->removeButton->setEnabled(false);
            this->callButon->setEnabled(false);
            break;
        }
        index++;
    }
}

void UserMenu::call()
{
    if (!this->app->getTcp()->isConnected()) {
        this->reconnectButton->show();
        return;
    }
    if (this->selection.id == -1)
        return;
    if (this->callWidget->getScene() != Call::Scene::NOCALL)
        return;
    app->call(this->selection);
    callWidget->setScene(Call::Scene::ONCALL, this->selection.username);
    callWidget->updateCall();
}
