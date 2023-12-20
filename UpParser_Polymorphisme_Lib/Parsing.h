#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include "Command.h"
#include "Target.h"

class Parsing {
public:
    Parsing();
 
    void parseCommandLine(int argc, char* argv[]);
    void printHelp() const;
    void addCommand(Command* command);
    void addTarget(Target* target);

private:
    // Helpers for the parseCommandLine Method
    bool isCommand(const std::string& arg) const;
    void processImmediateCommand(const std::string& command, const std::vector<std::string>& commandLine, size_t& i);
    void processNonImmediateCommand(const std::string& command, const std::vector<std::string>& commandLine, size_t& i);
    void processTargets(const std::vector<std::string>& commandLine);
    void checkRequiredCommands();
    void checkTargets();

    // Helpers for the printHelp Method
    void printCommand(const Command* command, std::set<std::string>& displayedCommands) const;
    void printCommands() const;
    void printTargets() const;

    std::unordered_map<std::string, Command*> commandMap;
    std::vector<Target*> targets;
    bool allowEmptyTargets;
    std::string executableName;
};
