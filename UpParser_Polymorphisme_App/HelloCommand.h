#pragma once

#include "../UpParser_Polymorphisme_Lib/Command.h"

class HelloCommand : public Command {
private:
    std::string nameToHello;
public:
    HelloCommand();
    void processArgs(const std::vector<std::string>& args);
    void execute();
};


