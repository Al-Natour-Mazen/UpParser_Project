#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>
#include <map>
#include "Command.h"


class Parsing {
public:
    Parsing();
    
    void checkRequiredCommands(const std::vector<std::string>& commandLine);
    void checkTargets(const std::vector<std::string>& commandLine);
    void parseCommandLine(int argc, char* argv[]);
    void printHelp() const;
    void addCommand(Command* command);

private:
    std::string executableName;
    bool allowEmptyTargets;
    std::vector<std::string> targets;
    std::map<std::string, Command*> commandMap;
    std::vector<std::pair<Command*, std::vector<std::string>>> immediateCommands;
    std::vector<std::pair<Command*, std::vector<std::string>>> nonimmediateCommands;

    void processCommands(std::vector<std::string>& commandLine);
    void processCommand(const std::string& arg, std::vector<std::string>& commandLine, size_t& i);
    std::vector<std::string> getCommandArguments(const std::string& arg, std::vector<std::string>& commandLine, size_t& i, int numArgs);
    void executeCommands(const std::vector<std::pair<Command*, std::vector<std::string>>>& commands);
    void processNonImmediateCommands(std::vector<std::string>& commandLine);
    void printCommand(const Command* command, std::set<std::string>& displayedCommands) const;
    void printCommands() const;
    bool isCommand(const std::string& arg) const;
};