#include "pch.h"
#include "HelloCommandBis.h"
#include <iostream>

HelloCommandBis::HelloCommandBis() : Command("hello", { "-hello" }, 1, "Print 'Hello, [Arg] !'", true, false) {}

void HelloCommandBis::processArgs(const std::vector<std::string>& args) {
    nameToHello = args[0];
}

void HelloCommandBis::execute() {
    executionTime = std::chrono::steady_clock::now();
    std::cout << "Hello, " << nameToHello << "!" << std::endl;
}
