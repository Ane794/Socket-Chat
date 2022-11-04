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
    auto serverConfig = YamlConfig().getServerConfig(),
            clientConfig = YamlConfig().getClientConfig();

    ip::udp::endpoint endpoint(
            ip::address::from_string(clientConfig["server"]["host"].as<std::string>()),
            clientConfig["server"]["port"].as<ip::port_type>()
    ), server(
            ip::address::from_string("127.0.0.1"),
            serverConfig["port"].as<ip::port_type>()
    );

    std::string msg;
    std::cout << " > ";
    while (std::getline(std::cin, msg)) {
        sendMsg(server, msg);
        sendMsg(endpoint, msg);
        std::cout << " > ";
    }
}
