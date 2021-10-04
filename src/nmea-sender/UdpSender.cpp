#include "UdpSender.hpp"

UdpSender::UdpSender()
    : io_service_()
    , socket_(io_service_)
{
}

UdpSender::~UdpSender() {
    close();
}

void UdpSender::open() {

    if(!socket_.is_open()) {
        socket_.open(boost::asio::ip::udp::v4());
    }
}

void UdpSender::close() {

    if (socket_.is_open()) {
        socket_.close();
    }
}

void UdpSender::sendTo(const std::string& ip, int port, const std::string& payload) {
    const auto endpoint = boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string(ip), 
        static_cast<unsigned short>(port));
        
    const auto buffer = boost::asio::buffer(payload.data(), payload.size());

    socket_.send_to(buffer, endpoint);
}