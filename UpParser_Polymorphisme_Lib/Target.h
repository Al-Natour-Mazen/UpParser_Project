#pragma once
#include <string>

class Target {
public:
    Target(const std::string& description, bool canBeEmpty);
    std::string getDescription() const;
    bool canTargetBeEmpty() const;

private:
    std::string description;
    bool canBeEmpty;
};

