#include "pch.h"
#include "Command.h"
#include <algorithm>

Command::Command(const std::string& name, const std::vector<std::string>& aliases,
    int numArgs, const std::string& description, bool required, bool immediate)
    : name(name), aliases(aliases), numArgs(numArgs),
    description(description), required(required), immediate(immediate), processed(false) {}

const std::string& Command::getName() const {
    return name;
}
int Command::getNumArgs() const {
    return numArgs;
}

bool Command::isRequired() const {
    return required;
}

bool Command::isImmediate() const {
    return immediate;
}

const std::vector<std::string>& Command::getAliases() const {
    return aliases;
}

const std::string& Command::getDescription() const {
    return description;
}

void Command::setProcessed(bool value) {
    processed = value;
}

bool Command::isProcessed() const {
    return processed;
}
