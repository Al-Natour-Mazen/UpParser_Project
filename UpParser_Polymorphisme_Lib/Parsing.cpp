#include "pch.h"
#include "Parsing.h"

// Constructor 
Parsing::Parsing(bool allowIfEmptyTargets) : allowEmptyTargets(allowIfEmptyTargets) {}


// Check for missing required commands and execute immediate commands if required
void Parsing::checkRequiredCommands(const std::vector<std::string>& commandLine) {
    for (const std::pair<const std::string, Command*>& entry : commandMap) {
        if (entry.second->isRequired()) {
            auto it = std::find(commandLine.begin(), commandLine.end(), entry.first);
            if (it == commandLine.end()) {
                throw std::invalid_argument("Missing required command: " + entry.first);
            }
        }
    }
}


// Check if targets are required and throw an error if they are not present
void Parsing::checkTargets(const std::vector<std::string>& commandLine) {
    if (commandLine.size() > 1 && targets.empty() && !allowEmptyTargets && !commandMap.empty()) {
        throw std::invalid_argument("At least one target is required.");
    }
}


void Parsing::parseCommandLine(int argc, char* argv[]) {
    executableName = argv[0];
    std::vector<std::string> commandLine(argv + 1, argv + argc);

    processCommands(commandLine);
   
    // Check if targets are required and throw an error if they are not present
    checkTargets(commandLine);

    // Check for required commands first
    checkRequiredCommands(commandLine);

    // Execute immediate commands
    executeCommands(immediateCommands);

    // Process non-immediate commands
    executeCommands(nonimmediateCommands);
}

void Parsing::processCommands(std::vector<std::string>& commandLine) {
    size_t i = 0;
    while (i < commandLine.size()) {
        const std::string& arg = commandLine[i];

        if (isCommand(arg)) {
            processCommand(arg, commandLine, i);
        } else {
            targets.push_back(arg); // It's a target
        }

        ++i;
    }
}

void Parsing::processCommand(const std::string& arg, std::vector<std::string>& commandLine, size_t& i) {
    if (commandMap.find(arg) != commandMap.end()) {
        Command* currentCommand = commandMap[arg];
        std::vector<std::string> args = getCommandArguments(arg, commandLine, i, currentCommand->getNumArgs());

        if (currentCommand->isImmediate()) {
            immediateCommands.emplace_back(currentCommand, args); // Collect immediate command for later execution
        } else {
            nonimmediateCommands.emplace_back(currentCommand, args); // Collect non-immediate command for later execution
        }
    } else {
        throw std::invalid_argument("Unrecognized command: " + arg); // Handle the case where an unrecognized command is encountered
    }
}

std::vector<std::string> Parsing::getCommandArguments(const std::string& arg, std::vector<std::string>& commandLine, size_t& i, int numArgs) {
    std::vector<std::string> args;
    for (int j = 0; j < numArgs; ++j) {
        size_t nextIndex = i + 1;
        if (nextIndex < commandLine.size() && !isCommand(commandLine[nextIndex])) {
            args.push_back(commandLine[nextIndex]);
            ++i;
        } else {
            throw std::invalid_argument("Missing arguments for command: " + arg + " , this commande need " + std::to_string(numArgs) + " arg(s).");
        }
    }

    return args;
}

void Parsing::executeCommands(const std::vector<std::pair<Command*, std::vector<std::string>>>& commands) {
    for (const std::pair<Command*, std::vector<std::string>>& command : commands) {
        if (!command.first->isProcessed()) {
            command.first->processArgs(command.second);
            command.first->execute();
            command.first->setProcessed(true);
        }
    }
}


// Print information about a command, avoiding duplication
void Parsing::printCommand(const Command* command, std::set<std::string>& displayedCommands) const {
    if (displayedCommands.find(command->getName()) == displayedCommands.end()) {
        std::cout << "\t" << command->getName();
        for (const std::string& alias : command->getAliases()) {
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

    for (const std::pair<const std::string, Command*>& entry : commandMap) {
        const Command* command = entry.second;
        printCommand(command, displayedCommands);
    }
}


// Print help information, including usage, commands, and targets
void Parsing::printHelp() const {
    std::cout << "Usage: " << executableName << " [ Commande ] Files+" << std::endl;
    std::cout << "\tFiles : Files to compile" << std::endl;

    // Print information about all commands
    printCommands();
}

// Add a command to the command map
void Parsing::addCommand(Command* command) {
    for (const std::string& alias : command->getAliases()) {
        commandMap[alias] = command;
    }
}

// Check if a given argument is a command
bool Parsing::isCommand(const std::string& arg) const {
    return arg.size() > 1 && arg[0] == '-';
}
