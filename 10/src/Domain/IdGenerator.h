//
// Created by flipd on 24.12.2024.
//

#ifndef IDGENERATOR_H
#define IDGENERATOR_H
#include <iomanip>
#include <random>

class IdGenerator {
public:
    static std::string GenerateId() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(0, 255);

        std::ostringstream ss;
        for (int i = 0; i < 16; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
        }
        return ss.str();
    }
};
#endif //IDGENERATOR_H
