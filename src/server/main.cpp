#include <iostream>
#include <asio.hpp>
#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")

#include "util/YamlConfig.h"


using namespace asio;

class Server {
    ip::port_type port;
    std::string notification;
public:
    explicit Server(ip::port_type port, std::string notification) :
            port(port),
            notification(std::move(notification)) {}

    [[noreturn]] void run() const {
        io_service service;
        char buff[1024];
        ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), port));

        while (true) {
            ip::udp::endpoint senderEndpoint;

            // 接收
            auto bytes = sock.receive_from(buffer(buff), senderEndpoint);
            std::string msg(buff, bytes);
            std::cout << msg << std::endl;
            sock.send_to(buffer(msg), senderEndpoint);

            // 停止播放音效.
            mciSendString(
                    (std::string("stop ") + notification).c_str(),
                    nullptr, 0, nullptr
            );
            // 播放音效.
            mciSendString(
                    (std::string("play ") + notification).c_str(),
                    nullptr, 0, nullptr
            );
        }
    }
};

int main() {
    auto config = YamlConfig().getServerConfig();

    Server(config["port"].as<int>(), config["notification"].as<std::string>()).run();
}
