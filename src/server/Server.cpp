#include "Server.h"

#include <iostream>

#ifdef _WIN32

#include <mmsystem.h>

#pragma comment (lib, "winmm.lib")

#endif // _WIN32

Server::Server(ip::port_type port, std::string notification, std::string selfName, std::string oppositeName) :
        port(port),
        notification(std::move(notification)),
        selfName(std::move(selfName)),
        oppositeName(std::move(oppositeName)) {}

void Server::run() const {
    io_service service;
    char buff[1024];
    ip::udp::socket sock(service, ip::udp::endpoint(ip::udp::v4(), port));

    while (true) {
        ip::udp::endpoint senderEndpoint;

        /* 接收. */
        auto bytes = sock.receive_from(buffer(buff), senderEndpoint);
        std::string msg(buff, bytes);

        /* 輸出時間. */
        time_t t = time(nullptr);
        char timeString[32];
        strftime(timeString, sizeof(timeString), "[%H:%M:%S]", localtime(&t));
        std::cout << timeString << " ";

        if (senderEndpoint.address() != ip::address::from_string("127.0.0.1")) {
            std::cout << oppositeName << " > " << msg << std::endl;

#ifdef _WIN32
            /* 停止播放音效. */
            mciSendString(
                    (std::string("stop ") + notification).c_str(),
                    nullptr, 0, nullptr
            );

            /* 播放音效. */
            mciSendString(
                    (std::string("play ") + notification).c_str(),
                    nullptr, 0, nullptr
            );
#endif // _WIN32

        } else {
            std::cout << selfName << " > " << msg << std::endl;
        }

        sock.send_to(buffer(msg), senderEndpoint);
    }
}
