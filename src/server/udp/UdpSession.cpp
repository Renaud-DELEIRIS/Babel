/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.cpp
*/

#include "server/UdpServer.hpp"
#include "../../../include/server/UdpServer.hpp"

UdpSession::UdpSession(UdpServer *server) : Server(server)
{
    this->recvBuffer.assign(0);
}

void UdpSession::handle_sent(const boost::system::error_code &ec, std::size_t)
{
    // here response has been sent
    if (ec)
    {
        std::cout << "Error sending response to " << remoteEndpoint
                  << ": " << ec.message() << "\n";
    }
}
