#pragma once
#include "Command.h"
#include <iostream>

class HelloCommand : public Command {
private:
    std::string nameToHello;
public:
    HelloCommand();
    void processArgs(const std::vector<std::string>& args) override;
    void execute() override;
};
