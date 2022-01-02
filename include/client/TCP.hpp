/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#include "security.hpp"

class App;

#ifndef TCP_HPP
    #define TCP_HPP

    #include <iostream>
    #include <string>
    #include <boost/array.hpp>
    #include <boost/asio.hpp>
    #include <QWidget>
    #include <queue>
    #include <mutex>

    #define TCP_IP "127.0.0.1"
    #define TCP_PORT 2000

    class TCP
    {
        public:
            TCP(App *appcopy, std::string ip = TCP_IP);
            ~TCP();

            std::string sendCommand(std::string command);
            bool isConnected() { sendCommand("EMPTY;EMPTY;/ping"); return this->_connected;};
            void doConnect();
            void read(const boost::system::error_code &error, size_t bytes_recvd);
            void async_read();

    private:
            boost::asio::io_context io_context;
            boost::asio::ip::tcp::socket *socket;
            bool _connected = true;
            boost::asio::io_service::strand strand;
            boost::array<std::bitset<16>, max_length> buf = {0};
            App *copy;
            std::queue<std::string> queue;
            std::mutex mutex;
    };

#endif /* TCP_HPP */