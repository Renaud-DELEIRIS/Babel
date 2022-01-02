/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include <QtGui>
#include <QApplication>
#include "GUI/App.h"
#include "client/protocol/ClientUdp.hpp"

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::string ip;

    if (argc == 2)
        ip = std::string(argv[1]);
    else
        ip = std::string(TCP_IP);
    App main_app(NULL, ip);
    main_app.show();
    return app.exec();
}
