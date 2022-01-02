/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#ifndef CHAT_MESSAGE_HPP
    #define CHAT_MESSAGE_HPP

    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <iostream>
    #include <list>
    #include <memory>
    #include <set>
    #include <vector>
    #include <utility>
    #include <algorithm>
    #include <string>
    #include <bitset>
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>
    #include <boost/array.hpp>

    #include "Signals.hpp"
    #include "Logs.hpp"
    #include "Asqlite3.hpp"
    #include "Protocol.hpp"
    #include "UdpServer.hpp"

    #define TCP_PORT 2000
    #define EMPTY "__EMPTY__"

    using boost::asio::ip::tcp;

    class TcpSession : public std::enable_shared_from_this<TcpSession>
    {
        public:
            TcpSession(boost::asio::io_service &, UdpServer *copy, std::mutex
            *copyMtx, std::vector<std::shared_ptr<TcpSession>> *allSessions,
            std::map<int, UserApp> *allUserApp);

            tcp::socket &getSocket();

            void start();
            void handleRead(std::shared_ptr<TcpSession> &, const
                boost::system::error_code &, std::size_t);

            typedef bool (TcpSession::*function_type)(std::string, struct UserApp);
            typedef UserApp (TcpSession::*function_get)(std::string);

            std::map<std::string, function_type> mapped = {
                { "/login", &TcpSession::login },
                { "/logout", &TcpSession::logout },
                { "/join", &TcpSession::join },
                { "/hangup", &TcpSession::hangup },
                { "/accept", &TcpSession::accept },
                { "/refuse", &TcpSession::refuse },
                { "/add", &TcpSession::add },
                { "/remove", &TcpSession::remove },
                { "/call", &TcpSession::call },
                { "/ping", &TcpSession::ping },
                { "/check", &TcpSession::check_user },
                { "/linked", &TcpSession::check_linked },
                { "/exit", &TcpSession::close_server },
                { "/getcontacts", &TcpSession::get_contacts },
                { "/getusersincall", &TcpSession::get_users_in_call }
            };

            std::map<std::string, function_get> getter = {
                { "/getuser", &TcpSession::get_user },
                { "/getuserbyid", &TcpSession::get_user_by_address }
            };

            // MAPPED
            bool login(std::string, struct UserApp);
            bool logout(std::string, struct UserApp);
            bool join(std::string, struct UserApp);
            bool hangup(std::string, struct UserApp);
            bool call(std::string, struct UserApp);
            bool ping(std::string, struct UserApp);
            bool close_server(std::string, struct UserApp);
            bool check_user(std::string, struct UserApp);
            bool check_linked(std::string, struct UserApp);
            bool get_contacts(std::string, struct UserApp);
            bool get_users_in_call(std::string, struct UserApp);
            bool accept(std::string, struct UserApp);
            bool refuse(std::string, struct UserApp);
            bool add(std::string, struct UserApp);
            bool remove(std::string, struct UserApp);

            // GETTER
            UserApp get_user();
            UserApp get_user(std::string);
            UserApp get_user_by_address(std::string);

            void display(UserApp);
            bool send(const char *);

            S_Protocol decode(std::string);

            std::string usersincall;
            std::vector<std::shared_ptr<TcpSession>> *allSessions;

        private:
            tcp::socket socket;

            Protocol *recv;
            boost::array<std::bitset<16>, max_length> buffer = {0};

            UserApp recvUser;
            Commands recvCommands;
            std::map<int, UserApp> *users;
            Asqlite3 database;
            void close_socket();
            UdpServer *voiceServer;
            std::mutex *mtx;
            std::map<std::string, UserApp> users_index;
    };

    class TcpServer
    {
        public:
            TcpServer(boost::asio::io_service &, short);

            void handle_accept(std::shared_ptr<TcpSession>, const
                boost::system::error_code &);

        private:
            boost::asio::io_service &ios;
            tcp::acceptor acceptor;
            UdpServer *voiceServer;
            std::mutex mtx;
            std::vector<std::shared_ptr<TcpSession>> allSessions;
            std::map<int, UserApp> users;
    };

#endif // CHAT_MESSAGE_HPP
