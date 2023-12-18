#pragma once

#include <vector>
#include <unordered_map>
#include "Commande.h"

class Parsing {
public:
    Parsing();

    void parseCommandLine(const std::vector<std::string>& commandLine);

    void printHelp() const;

    void addCommand(Command* command);

    void setExecutableName(const std::string& name);

private:
    bool isCommand(const std::string& arg) const;

    std::unordered_map<std::string, Command*> commandMap;

    std::vector<std::string> targets;
    bool allowEmptyTargets;
    std::string executableName;
};

