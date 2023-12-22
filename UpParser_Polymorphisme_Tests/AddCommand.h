#pragma once
#include "../UpParser_Polymorphisme_Lib/Command.h"
#include <vector>
#include <string>

class AddCommand : public Command {
private:
    int number1;
    int number2;
public:
    AddCommand();
    void processArgs(const std::vector<std::string>& args) override;
    void execute() override;
};
