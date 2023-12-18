#pragma once
#include <string>
class Target {
public:
    Target(const std::string& description, bool canBeEmpty)
        : description(description), canBeEmpty(canBeEmpty) {}

private:
    std::string description;
    bool canBeEmpty;
};

