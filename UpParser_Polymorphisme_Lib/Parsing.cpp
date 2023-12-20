#include "pch.h"
#include "Parsing.h"
#include <iostream>


// Constructor 
Parsing::Parsing() : allowEmptyTargets(false) {}

// Process immediate command based on the provided command name and command line arguments
void Parsing::processImmediateCommand(const std::string& command, const std::vector<std::string>& commandLine, size_t& i) {
    auto it = commandMap.find(command);
    if (it != commandMap.end() && it->second->isImmediate()) {
        std::vector<std::string> args;
        size_t nextIndex = i + 1;

        for (int j = 0; j < it->second->getNumArgs(); ++j) {
            if (nextIndex < commandLine.size()) {
                args.push_back(commandLine[nextIndex]);
                ++nextIndex;
            }
            else {
                throw std::invalid_argument("Missing arguments for command: " + command);
            }
        }

        // Process and execute the immediate command
        it->second->processArgs(args);
        it->second->execute();
        it->second->setProcessed(true);
    }
}

// Process non-immediate command based on the provided command name and command line arguments
void Parsing::processNonImmediateCommand(const std::string& command, const std::vector<std::string>& commandLine, size_t& i) {
    auto it = commandMap.find(command);
    if (it != commandMap.end() && !it->second->isImmediate()) {
        std::vector<std::string> args;
        for (int j = 0; j < it->second->getNumArgs(); ++j) {
            size_t nextIndex = i + 1;
            if (nextIndex < commandLine.size()) {
                args.push_back(commandLine[nextIndex]);
                ++i; // Increment i to skip processed arguments
            }
            else {
                throw std::invalid_argument("Missing arguments for command: " + command);
            }
        }

        // Process and execute the non-immediate command
        it->second->processArgs(args);
        it->second->execute();
        it->second->setProcessed(true);
    }
}

// Process and add targets to the 'targets' vector
void Parsing::processTargets(const std::vector<std::string>& commandLine) {
    for (const auto& arg : commandLine) {
        if (!isCommand(arg)) {
            // Add target to the 'targets' vector
            Target* target = new Target(arg, true); // Adjust based on your implementation
            targets.push_back(target);
        }
    }
}

// Check for missing required commands and execute immediate commands if required
void Parsing::checkRequiredCommands() {
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

// Check if targets are required and throw an error if they are not present
void Parsing::checkTargets() {
    if (targets.empty() && !allowEmptyTargets) {
        throw std::invalid_argument("At least one target is required.");
    }
}

// Parse the command line arguments
void Parsing::parseCommandLine(int argc, char* argv[]) {
    executableName = argv[0];
    const std::vector<std::string> commandLine(argv + 1, argv + argc);
    size_t i = 0;

    // Process immediate commands first
    while (i < commandLine.size()) {
        const std::string& arg = commandLine[i];

        if (isCommand(arg)) {
            // Check if the command is registered in the commandMap
            if (commandMap.find(arg) != commandMap.end()) {
                processImmediateCommand(arg, commandLine, i);
            }
            else {
                // Handle the case where an unrecognized command is encountered
                throw std::invalid_argument("Unrecognized command: " + arg);
            }
           
        }

        ++i;
    }

    // Process non-immediate commands
    for (size_t i = 0; i < commandLine.size(); ++i) {
        const std::string& arg = commandLine[i];

        if (isCommand(arg)) {

            // Check if the command is registered in the commandMap
            if (commandMap.find(arg) != commandMap.end()) {
                processNonImmediateCommand(arg, commandLine, i);
            }
            else {
                // Handle the case where an unrecognized command is encountered
                throw std::invalid_argument("Unrecognized command: " + arg);
            }
        }
    }

    // Process and add targets
    processTargets(commandLine);

    // Check for missing required commands
    checkRequiredCommands();

    // Check if targets are present
    checkTargets();
}

// Print information about a command, avoiding duplication
void Parsing::printCommand(const Command* command, std::set<std::string>& displayedCommands) const {
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

// Print information about all commands
void Parsing::printCommands() const {
    std::cout << "Options:" << std::endl;

    // Keep track of displayed commands to avoid duplication
    std::set<std::string> displayedCommands;

    for (const auto& entry : commandMap) {
        const Command* command = entry.second;
        printCommand(command, displayedCommands);
    }
}

// Print information about all targets
void Parsing::printTargets() const {
    std::cout << "Targets:" << std::endl;
    for (const auto& target : targets) {
        std::cout << "\t" << target->getDescription() << " (Can be empty: " << (target->canTargetBeEmpty() ? "Yes" : "No") << ")" << std::endl;
    }
}

// Print help information, including usage, commands, and targets
void Parsing::printHelp() const {
    std::cout << "Usage: " << executableName << " [ --help|-h ] Files+" << std::endl;
    std::cout << "\tFiles : Files to compile" << std::endl;

    // Print information about all commands
    printCommands();

    // Print information about all targets
    printTargets();
}

// Add a command to the command map
void Parsing::addCommand(Command* command) {
    commandMap[command->getName()] = command;
    for (const auto& alias : command->getAliases()) {
        commandMap[alias] = command;
    }
}

// Add a target to the 'targets' vector
void Parsing::addTarget(Target* target) {
    targets.push_back(target);
}


// Check if a given argument is a command
bool Parsing::isCommand(const std::string& arg) const {
    return arg.size() > 1 && arg[0] == '-';
}