/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Udp
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <array>
#include <iostream>
#define UPD_PORT 2001

#include "client/sound/Sound.hpp"


class ClientUdp {
    public:
        ClientUdp(const std::string ip, boost::asio::io_service &ioService,
                  Sound::RecorderPlayer player);
        ~ClientUdp();

        void sendMessage(const std::string &msg);
        void sendMessage(const std::vector<unsigned char> &msg);

        void getMessage();
        void read(const boost::system::error_code &error, size_t bytes_recvd);

protected:
    private:
        boost::asio::ip::udp::endpoint receiverEndpoint;
        boost::asio::ip::udp::socket *sock;
        Sound::Codec codec;
        Sound::RecorderPlayer player;
        std::vector<unsigned char> recvVec;
        std::array<unsigned char, 120> recv;
        boost::asio::io_service::strand strand;
};


#endif /* !UDP_HPP_ */
