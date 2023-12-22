#include "HelloCommand.h"
#include <iostream>

HelloCommand::HelloCommand() : Command("hello", { "-hello" }, 1, "Print 'Hello, [Args] !'", false, false) {}

void HelloCommand::processArgs(const std::vector<std::string>& args) {
    nameToHello = args[0];
}

void HelloCommand::execute() {
    std::cout << "Hello, " << nameToHello << "!" << std::endl;
}
