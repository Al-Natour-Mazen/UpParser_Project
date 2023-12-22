#pragma once
#include "../UpParser_Polymorphisme_Lib/Command.h"
#include <vector>
#include <string>

extern std::vector<std::string> executionOrder;

class TestCommand : public Command {
private:
    std::string commandName;
public:
    TestCommand(const std::string& name);
    void processArgs(const std::vector<std::string>& args) override;
    void execute() override;
};


