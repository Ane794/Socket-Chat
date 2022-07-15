#ifndef SOCKET_CHAT_YAMLCONFIG_H
#define SOCKET_CHAT_YAMLCONFIG_H

#include <yaml-cpp/yaml.h>

class YamlConfig {
    std::string path;
    YAML::Node config;

public:
    explicit YamlConfig(std::string path = "config.yml");

    YAML::Node getServerConfig();

    YAML::Node getClientConfig();
};


#endif //SOCKET_CHAT_YAMLCONFIG_H
