/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/

#include <QtGui>
#include "App.h"
#include "Login.h"
#include "UserMenu.h"

#include <iostream>

#define USERCMDPARAM(cmd, param) this->user.username + ";" + this->user.password + ";" + cmd + ";" + param
#define USERCMD(cmd) this->user.username + ";" + this->user.password + ";" + cmd

App::App(QWidget *parent, std::string ip) : QWidget(parent)
{
    setWindowTitle("Babel");
    this->client = new TCP(this, ip);
    // std::thread voiceT(&App::initVoiceClient, this, ip);
    // voiceT.detach();
    update();
}

void App::initVoiceClient(std::string ip)
{
    boost::asio::io_service ioService;
    this->clientudp = new ClientUdp(ip, ioService, Sound::RecorderPlayer());
}

std::vector<UserApp> App::getUserInCall() const
{
    std::string response = this->client->sendCommand(std::string(USERCMD("/getusersincall")));
    std::cout << response << "\n";
    std::stringstream ss(response);
    std::string item;
    std::vector<UserApp> elems;
    while (std::getline(ss, item, '\n')) {
        UserApp user_from_string = convertUserFromString(item);
        if (user_from_string.username == "")
            continue;
        elems.push_back(user_from_string);
    }
    return elems;
}

UserApp App::convertUserFromString(std::string response)
{
    std::stringstream ss(response);
    std::string item;
    std::vector<std::string> elems;
    if (std::count(response.begin(), response.end(), ';') != 3)
        return UserApp();
    while (std::getline(ss, item, ';')) {
        elems.push_back(item);
    }
    int id;
    try {
        id = std::stoi(elems[3]);
    } catch (std::exception &e) {
        std::cout << e.what() << " : " << "bad id in convertUserFromString" << std::endl;
        return UserApp();
    }
    return UserApp(elems[0], elems[1], elems[2], id);
}

UserApp App::getUser(std::string username) const
{
    std::string response = this->client->sendCommand(std::string(USERCMDPARAM("/getuser", username)));
    if (response == "user not found")
        return UserApp();
    return convertUserFromString(response);
}

void App::call(UserApp user)
{
    std::string response = this->client->sendCommand(std::string(USERCMDPARAM("/call", user.username)));
    std::cout << "-->" << "|" << response << "|" << "\n";
    response = response.substr(response.find("calling...") + 1, response.length());
    std::cout << "-" << response << "-" << "\n";
    idGroup = std::atoi(response.c_str());
}

void App::hangup()
{
    idGroup = -1;
    this->client->sendCommand(USERCMD("/hangup"));
}

void App::acceptCall()
{
    // idGroup is get in the async part on "accept?[groupId]" command
    std::string response = this->client->sendCommand(USERCMD("/accept;" + std::to_string(this->idGroup)));
    idGroup = std::atoi(response.c_str());
    updateCall();
}

void App::refuseCall()
{
    this->idGroup = -1;
    this->client->sendCommand(USERCMD("/refuse"));
}

void App::addContactToCall(UserApp contact_to_add)
{
    //TODO ADD CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN YOUR CONTACT
    //NEED TO CHECK IF USER ONLINE
}

void App::removeContactToCall(UserApp contact_to_remove)
{
    //TODO REMOVE CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN THE CALL
}

bool App::addContact(std::string user)
{
    std::string response = this->client->sendCommand(std::string(USERCMDPARAM("/add", user)));

    std::cout << response << std::endl;
    if (response == "true")
        return true;
    return false;
}

bool App::removeContact(std::string user)
{
    std::string response = this->client->sendCommand(std::string(USERCMDPARAM("/remove", user)));

    if (response == "true")
        return true;
    return false;
}

bool App::checkUser(std::string username)
{
    std::string response = this->client->sendCommand(std::string(USERCMDPARAM("/check", username)));

    if (response == "true")
        return true;
    return false;
}

std::vector<UserApp> App::fetchContact() const
{
    std::string response = this->client->sendCommand(std::string(USERCMD("/getcontacts")));
    std::stringstream ss(response);
    std::string item;
    std::vector<UserApp> elems;
    while (std::getline(ss, item, '\n')) {
        UserApp user = convertUserFromString(item);
        if (user.username == "")
            continue;
        elems.push_back(user);
    }
    return elems;
}

loginCode App::login(std::string username, std::string password)
{
    std::string response = this->client->sendCommand(std::string(username + ";" + password + ";" + "/login"));
    std::cout << response << std::endl;
    if (response == "BAD_PASSWORD")
        return BAD_PASSWORD;
    if (response == "not connected" || response == "")
        return NOT_CONNECTED;
    this->app_state = Menu_;
    this->user = UserApp(username, "", password, std::atoi(response.c_str()));
    return SUCCESS;
}

void App::update()
{
    switch(this->app_state) {
        case ToLog:
            loginui = new Login(this);
            break;
        case Menu_:
            delete loginui;
            this->usermenu = new UserMenu(this);
            break;
    }
}

void App::updateCall() const
{
    usermenu->getCallW()->updateCall();
}

void App::receiveCall(std::string caller)
{
    this->usermenu->getCallW()->setScene(Call::Scene::RECEIVECALL, caller);
}

void App::setGroupId(int newId)
{
    this->idGroup = newId;
}

UserMenu *App::getUsermenu()
{
    return usermenu;
}
