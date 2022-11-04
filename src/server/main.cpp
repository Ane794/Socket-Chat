#include "Server.h"
#include "util/YamlConfig.h"

int main() {
    auto config = YamlConfig().getServerConfig();

    Server(
            config["port"].as<int>(),
            config["notification"].as<std::string>(),
            config["selfName"].as<std::string>(),
            config["oppositeName"].as<std::string>()
    ).run();
}
