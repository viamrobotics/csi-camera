#pragma once

#include <iostream>
#include <string>
#include <fstream> 

#define DEVICE_PATH "/proc/device-tree/model"

struct device_type {
    enum type {
        unknown,
        jetson,
        pi
    };
    type value;
    std::string name;

    device_type(type value, std::string name) : value(value), name(name) {}
};

device_type get_device_type() {
    std::ifstream device_name(DEVICE_PATH);
    if (device_name.is_open()) {
        std::string line;
        while (std::getline(device_name, line)) {
            std::string lowercase_line = line;
            std::transform(lowercase_line.begin(), lowercase_line.end(), lowercase_line.begin(), ::tolower);
            // Check for specific terms in a case-insensitive manner
            if (lowercase_line.find("nvidia") != std::string::npos &&
                (lowercase_line.find("orin") != std::string::npos ||
                 lowercase_line.find("nano") != std::string::npos ||
                 lowercase_line.find("agx") != std::string::npos ||
                 lowercase_line.find("jetson") != std::string::npos)) {
                return device_type(device_type::jetson, "Jetson");
            } else if (lowercase_line.find("raspberry") != std::string::npos &&
                lowercase_line.find("pi") != std::string::npos) {
                return device_type(device_type::pi, "Raspberry Pi");
            }
        }
        device_name.close();
    }

    return device_type(device_type::unknown, "unkwnown");
}
