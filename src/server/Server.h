#ifndef SOCKET_CHAT_SERVER_H
#define SOCKET_CHAT_SERVER_H

#include <asio.hpp>

using namespace asio;

class Server {
    ip::port_type port;
    std::string notification;
    std::string selfName, oppositeName;

public:
    Server(ip::port_type port, std::string notification, std::string selfName, std::string oppositeName);

    [[noreturn]] void run() const;
};

#endif //SOCKET_CHAT_SERVER_H
