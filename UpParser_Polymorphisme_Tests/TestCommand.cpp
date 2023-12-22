#include "pch.h"
#include "TestCommand.h"
#include <iostream>

std::vector<std::string> executionOrder;

TestCommand::TestCommand(const std::string& name) : Command(name, { "-" + name }, 1, name + " [args]", false, false), commandName(name) {}

void TestCommand::processArgs(const std::vector<std::string>& args) {}

void TestCommand::execute() {
    // Save the command name in the execution order.
    executionOrder.push_back(commandName);
}
