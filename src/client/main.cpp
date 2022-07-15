#include <iostream>
#include <asio.hpp>
#include "util/YamlConfig.h"

using namespace asio;

void sendMsg(const ip::udp::endpoint &endpoint, std::string msg) {
    io_service service;
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), 0));
    sock.send_to(buffer(msg), endpoint);
    char buff[1024];
    ip::udp::endpoint senderEndpoint;
    sock.receive_from(buffer(buff), senderEndpoint);
    sock.close();
}

int main() {
    auto config = YamlConfig().getClientConfig();

    ip::udp::endpoint endpoint(
            ip::address::from_string(config["server"]["host"].as<std::string>()),
            config["server"]["port"].as<ip::port_type>()
    );

    std::string msg;
    while (std::getline(std::cin, msg)) {
        sendMsg(endpoint, msg);
    }
}
