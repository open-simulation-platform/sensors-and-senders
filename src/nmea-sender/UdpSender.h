#pragma once

#include <boost/asio.hpp>

class UdpSender {
public:

    UdpSender();
    ~UdpSender();
    
    void open();
    void close();
    void sendTo(const std::string& ip, int port, const std::string& payload);

private:

    boost::asio::io_service io_service_;
    boost::asio::ip::udp::endpoint receiver_endpoint_;
    boost::asio::ip::udp::socket socket_;
};