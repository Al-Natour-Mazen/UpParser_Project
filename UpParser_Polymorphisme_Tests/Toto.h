#pragma once
#include "../UpParser_Polymorphisme_Lib/Command.h"
#include <vector>
#include <string>
#include <chrono>

class Toto : public Command {
public:
    std::chrono::steady_clock::time_point executionTime;
    Toto();
    void processArgs(const std::vector<std::string>& args) override;
    void execute() override;
};


