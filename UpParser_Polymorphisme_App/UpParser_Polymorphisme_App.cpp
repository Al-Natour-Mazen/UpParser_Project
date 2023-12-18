// UpParser_Polymorphisme_App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <Parsing.h>
#include <Commande.h>
#include <HelpCommand.h>
#include "HelloCommand.h"

int main(int argc, char* argv[]) {
    // Create an instance of Parsing
    Parsing parsing;
    parsing.setExecutableName(argv[0]);

    // Create a list of Command pointers
    std::vector<Command*> commands;

    // Create an instance of HelpCommand and add it to the list
    commands.push_back(new HelpCommand(&parsing));
    commands.push_back(new HelloCommand());

    // Add the commands to the Parsing instance
    for (Command* command : commands) {
        parsing.addCommand(command);
    }

    // Convert command line arguments to a vector of strings
    //std::vector<std::string> args(argv + 1, argv + argc);

    // Create a list of 
    std::vector<std::string> args = { "-hello","mazen44mazen2 mazen3","-h"};

    // Parse the command line arguments
    try {
        parsing.parseCommandLine(args);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        parsing.printHelp();

        // delete the commands at the end to avoid memory leaks
        for (Command* command : commands) {
            delete command;
        }

        return 1;
    }

    // delete the commands at the end to avoid memory leaks
    for (Command* command : commands) {
        delete command;
    }

    return 0;
}

