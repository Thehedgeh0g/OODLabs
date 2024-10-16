//
// Created by thehedgeh0g on 16.10.24.
//

#ifndef CONFIGPROVIDER_H
#define CONFIGPROVIDER_H
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigProvider {
public:
    explicit ConfigProvider(const std::string& configFilePath) {
        std::ifstream configFile(configFilePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open config file: " + configFilePath);
        }

        configFile >> m_configJson;
    }

    [[nodiscard]] std::string getOutputPath() const {
        return m_configJson.at("outputPath").get<std::string>();
    }

    [[nodiscard]] std::string getInputPath() const {
        return m_configJson.at("inputPath").get<std::string>();
    }

private:
    json m_configJson{};
};

#endif //CONFIGPROVIDER_H
