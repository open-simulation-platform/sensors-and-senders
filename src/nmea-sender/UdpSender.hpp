#pragma once

#include <boost/asio.hpp>
#include <string>

class UdpSender {
public:

    UdpSender();
    ~UdpSender();
    
    void open();
    void close();
    void send_to(const std::string& ip, int port, const std::string& payload);

private:

    boost::asio::io_service m_io_service;
    boost::asio::ip::udp::endpoint m_receiver_endpoint;
    boost::asio::ip::udp::socket m_socket;
};