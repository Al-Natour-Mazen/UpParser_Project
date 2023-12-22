#include "pch.h"
#include "HelpCommand.h"
#include "Parsing.h"

HelpCommand::HelpCommand(Parsing* parsToAdd) : Command("help", { "-h" }, 0, "Print this help", true, true), parsing(parsToAdd) {}

void HelpCommand::processArgs(const std::vector<std::string>& args) {
    // no arguments for the help command
}

void HelpCommand::execute() {
    if (parsing != nullptr) {
        parsing->printHelp();
    }
}

void HelpCommand::setParsing(Parsing* parsing) {
    this->parsing = parsing;
}
