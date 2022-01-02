/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Group.cpp
*/

#include "server/UdpServer.hpp"
#include "../../../include/server/UdpServer.hpp"


Group::Group()
{
}

Group::Group(shared_session session)
{
    this->sessions.push_back(session);
}

Group::Group(std::vector<shared_session> sessions)
{
    for (auto &session : sessions)
        this->sessions.push_back(session);
}

Group::~Group()
{
}

int Group::addSession(const std::string addressPort, int id,
                      std::vector<shared_session> allSessions)
{
    size_t find = addressPort.find(':');
    std::string address = addressPort.substr(0, find);
    std::cout << address << " \n";
    std::cout << addressPort.substr(find, address.length()) << " \n";
    int port = std::stoi(addressPort.substr(find + 1, address.length()));

    for (auto session : allSessions)
        if (session->remoteEndpoint.address().to_string() == address &&
            session->remoteEndpoint.port() == port) {
            session->id = id;
            this->addSession(session);
            return 0;
        }
    return 1;
}

void Group::addSession(const shared_session &session)
{
    for (auto _session : sessions)
        if (_session == session)
            return;
    this->sessions.push_back(session);
}

void Group::addSession(const std::vector<shared_session> sessions)
{
    for (auto &session: sessions)
        this->sessions.push_back(session);
}
