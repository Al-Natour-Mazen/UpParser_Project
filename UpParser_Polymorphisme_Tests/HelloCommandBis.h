#pragma once
#include "../UpParser_Polymorphisme_Lib/Command.h"
#include <vector>
#include <string>
#include <chrono>

class HelloCommandBis : public Command {
private:
    std::string nameToHello;
public:
    std::chrono::steady_clock::time_point executionTime;
    HelloCommandBis();
    void processArgs(const std::vector<std::string>& args) override;
    void execute() override;
};


