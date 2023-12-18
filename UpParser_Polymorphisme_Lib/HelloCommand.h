#pragma once
#include "Commande.h"
#include <iostream>

class HelloCommand : public Command {
private:
    std::string nameToHello;
public:
    HelloCommand() : Command("hello", { "-hello"}, 1, "Print 'Hello, World!'", false, true) {}

    void processArgs(const std::vector<std::string>& args) override {
        nameToHello = args.front();
    }

    void execute() override {
        std::cout << "Hello, " << nameToHello << "!" << std::endl;
    }
};

