// UpParser_Polymorphisme_App.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "../UpParser_Polymorphisme_Lib/Parsing.h"
#include "../UpParser_Polymorphisme_Lib/Command.h"
#include "../UpParser_Polymorphisme_Lib/HelpCommand.h"
#include "../UpParser_Polymorphisme_Lib/Target.h"

#include "HelloCommand.h"

int main(int argc, char* argv[]) {
    // TEST with VS with argv options : -hello mazen -hello tata *.png -hello bob -h

    // Check if there are enough command line arguments
    if (argc < 1) {
        std::cerr << "Error: Insufficient command line arguments." << std::endl;
        return 1;
    }

    // Create an instance of Parsing
    Parsing parsing;

    // Create a list of Command pointers
    std::vector<Command*> commands;

    // Create an instance of HelpCommand and add it to the list
    commands.push_back(new HelpCommand(&parsing));
    commands.push_back(new HelloCommand());

    Target* target= new Target("recupere quelque chose", false);

    parsing.addTarget(target);

    // Add the commands to the Parsing instance
    for (Command* command : commands) {
        parsing.addCommand(command);
    }

    // Parse the command line arguments
    try {
        parsing.parseCommandLine(argc,argv);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        parsing.printHelp();

        // delete the commands 
        for (Command* command : commands) {
            delete command;
        }

        return 1;
    }

    // delete the commands 
    for (Command* command : commands) {
        delete command;
    }

    delete target;

    return 0;
}

