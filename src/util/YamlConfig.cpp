#include "YamlConfig.h"

#include <iostream>

YamlConfig::YamlConfig(std::string path) :
        path(std::move(path)) {
    config = YAML::LoadFile(this->path);
}

YAML::Node YamlConfig::getServerConfig() {
    return config["server"];
}

YAML::Node YamlConfig::getClientConfig() {
    return config["client"];
}
