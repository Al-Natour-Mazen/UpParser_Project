#include "pch.h"
#include "Parsing.h"
#include <iostream>
#include <set>

Parsing::Parsing() : allowEmptyTargets(false) {}

void Parsing::parseCommandLine(const std::vector<std::string>& commandLine) {
    size_t i = 0;

    // Process immediate commands first
    while (i < commandLine.size()) {
        const std::string& arg = commandLine[i];

        if (isCommand(arg)) {
            auto it = commandMap.find(arg);
            if (it != commandMap.end() && it->second->isImmediate()) {
                std::vector<std::string> args;
                size_t nextIndex = i + 1;

                for (int j = 0; j < it->second->getNumArgs(); ++j) {
                    if (nextIndex < commandLine.size()) {
                        args.push_back(commandLine[nextIndex]);
                        ++nextIndex;
                    }
                    else {
                        throw std::invalid_argument("Missing arguments for command: " + arg);
                    }
                }

                it->second->processArgs(args);
                it->second->execute();
                it->second->setProcessed(true);
            }
        }

        ++i;
    }

    // Process non-immediate commands and targets
    for (size_t i = 0; i < commandLine.size(); ++i) {
        const std::string& arg = commandLine[i];

        if (isCommand(arg)) {
            auto it = commandMap.find(arg);
            if (it != commandMap.end() && !it->second->isImmediate()) {
                std::vector<std::string> args;
                for (int j = 0; j < it->second->getNumArgs(); ++j) {
                    size_t nextIndex = i + 1;
                    if (nextIndex < commandLine.size()) {
                        args.push_back(commandLine[nextIndex]);
                        ++i; // Increment i to skip processed arguments
                    }
                    else {
                        throw std::invalid_argument("Missing arguments for command: " + arg);
                    }
                }

                it->second->processArgs(args);

                // Execute non-immediate commands
                it->second->execute();
                it->second->setProcessed(true);
            }
        }
        else {
            targets.push_back(arg);
        }
    }
    // Check for missing required commands
    for (const auto& entry : commandMap) {
        if (entry.second->isRequired() && !entry.second->isProcessed()) {
            if (entry.second->isImmediate()) {
                // For immediate commands, execute and mark as processed
                entry.second->execute();
                entry.second->setProcessed(true);
            }
            else {
                // For non-immediate commands, throw an error
                throw std::invalid_argument("Missing required command: " + entry.first);
            }
        }
    }

}

void Parsing::printHelp() const {
    std::cout << "Usage: " << executableName << " [ --help|-h ] Files+" << std::endl;
    std::cout << "\tFiles : Files to compile" << std::endl;
    std::cout << "Options:" << std::endl;

    // Keep track of displayed commands to avoid duplication
    std::set<std::string> displayedCommands;

    for (const auto& entry : commandMap) {
        const Command* command = entry.second;

        // Check if the command has already been displayed
        if (displayedCommands.find(command->getName()) == displayedCommands.end()) {
            std::cout << "\t" << command->getName();
            for (const auto& alias : command->getAliases()) {
                std::cout << "|" << alias;
            }
            if (command->getNumArgs() > 0) {
                std::cout << " Args";
            }
            std::cout << " : " << command->getDescription() << std::endl;

            // Mark the command as displayed
            displayedCommands.insert(command->getName());
        }
    }
}


void Parsing::addCommand(Command* command) {
    commandMap[command->getName()] = command;
    for (const auto& alias : command->getAliases()) {
        commandMap[alias] = command;
    }
}

void Parsing::setExecutableName(const std::string& name) {
    executableName = name;
}

bool Parsing::isCommand(const std::string& arg) const {
    return arg.size() > 1 && arg[0] == '-';
}
