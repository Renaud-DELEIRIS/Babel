/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/


#ifndef BABEL_APP_H
#define BABEL_APP_H

#include "common/User.hpp"
#include "client/protocol/ClientUdp.hpp"
#include "client/TCP.hpp"

class UserMenu;

#include <QWidget>
#include <QtWidgets>
#include <QList>
#include <QLineEdit>
#include <string>

enum loginCode {SUCCESS, USER_NOT_EXIST, NOT_CONNECTED, BAD_PASSWORD};
//TODO REMOVEAND USE SQLITE

class  App : public QWidget
{
    Q_OBJECT

    public:
        App(QWidget *parent=NULL, std::string ip = TCP_IP);
        virtual ~App() {
            delete voiceThread;
        };
        std::vector<UserApp> fetchContact() const;
        bool checkUser(std::string usr);
        void hangup();
        UserApp getUser(std::string username) const;
        std::vector<UserApp> getUserInCall() const;
        void updateCall() const;

        void receiveCall(std::string caller);
        UserMenu *getUserMenu() const { return this->usermenu;};

        void initVoiceClient(std::string ip);
        void call(UserApp user_to_call);
        void acceptCall();
        void refuseCall();

        void addContactToCall(UserApp user_to_add);
        void removeContactToCall(UserApp user_to_remove);

        bool addContact(std::string user_to_add);
        bool removeContact(std::string user_to_remove);

        UserApp getContext() const { return this->user;};

        loginCode login(std::string username, std::string password);
        void update();

        static UserApp convertUserFromString(std::string username);
        void setGroupId(int newId);
        UserMenu *getUsermenu();
        TCP *getTcp() const { return this->client;};

    private:
        enum AppState {ToLog, Menu_};
        UserApp user = {"martin", "cringe", "127.0.0.1", 1};
        AppState app_state = ToLog;

        QLineEdit *search_name;
        QWidget *loginui;
        UserMenu *usermenu;
        TCP *client;
        ClientUdp *clientudp;
        int idGroup = -1;
        std::thread *voiceThread;
};

#endif //BABEL_APP_H
