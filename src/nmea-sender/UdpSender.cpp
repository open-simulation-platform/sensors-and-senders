#include "UdpSender.hpp"

UdpSender::UdpSender()
    : m_io_service()
    , m_socket(m_io_service)
{
}

UdpSender::~UdpSender() {
    close();
}

void UdpSender::open() {

    if(!m_socket.is_open()) {
        m_socket.open(boost::asio::ip::udp::v4());
    }
}

void UdpSender::close() {

    if (m_socket.is_open()) {
        m_socket.close();
    }
}

void UdpSender::send_to(const std::string& ip, int port, const std::string& payload) {
    const auto endpoint = boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string(ip), 
        static_cast<unsigned short>(port));
        
    const auto buffer = boost::asio::buffer(payload.data(), payload.size());

    m_socket.send_to(buffer, endpoint);
}