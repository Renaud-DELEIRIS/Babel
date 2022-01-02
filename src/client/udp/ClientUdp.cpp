/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Udp
*/

#include <boost/array.hpp>
#include "client/protocol/ClientUdp.hpp"

using boost::asio::ip::udp;

ClientUdp::ClientUdp(const std::string ip, boost::asio::io_service &ioService,
                     Sound::RecorderPlayer player) :
    codec(player.getSampleRate(), player.getChannelNumber(), player.getBufferSize()), strand(ioService)
{
    this->player = player;
    this->player.init();

    udp::resolver resolver(ioService);
    this->receiverEndpoint = udp::endpoint(boost::asio::ip::address::from_string(ip), 2001);
    this->sock = new udp::socket(ioService);
    this->sock->open(udp::v4());
    getMessage();
    // <------>
    ioService.run();

}

ClientUdp::~ClientUdp()
{
    this->sock->close();
}

void ClientUdp::sendMessage(const std::string &msg)
{
    this->sock->send_to(boost::asio::buffer(msg), this->receiverEndpoint);
}

void ClientUdp::sendMessage(const std::vector<unsigned char> &msg)
{
    this->sock->async_send_to(boost::asio::buffer(msg),
                              this->receiverEndpoint,
                              strand.wrap(
                                  boost::bind(
                                      &ClientUdp::getMessage,
                                      this
                                  )
                              )
                          );
}

void ClientUdp::read(const boost::system::error_code &error, size_t bytes_recvd)
{
    if (error) {
        std::cout << error.message() << std::endl;
        return;
    }
    this->recvVec = std::vector(recv.begin(),  recv.end());
    player.frameToSpeaker(codec.decodeFrames(this->recvVec));
}

void ClientUdp::getMessage()
{
    udp::endpoint senderEndpoint;

    this->sock->async_receive(boost::asio::buffer(recv),
                              strand.wrap(
                                  boost::bind(
                                      &ClientUdp::read,
                                      this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred
                                  )
                              )
    );
    this->sendMessage(codec.encodeFrames(player.getMic()));
}

/*
    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), SERVER_IP, MESSAGE ???);
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io_service);0
    socket.open(udp::v4());

    boost::array<char, 1> send_buf  = { 0 };
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
 */
