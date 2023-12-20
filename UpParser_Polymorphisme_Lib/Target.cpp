#include "pch.h"
#include "Target.h"

// Constructor 
Target::Target(const std::string& description, bool canBeEmpty)
    : description(description), canBeEmpty(canBeEmpty) {}

// Getter the description of the Target
std::string Target::getDescription() const {
    return description;
}

// Getter if the Target can be empty
bool Target::canTargetBeEmpty() const {
    return canBeEmpty;
}