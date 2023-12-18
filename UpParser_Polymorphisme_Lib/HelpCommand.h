#pragma once
#include "Commande.h"

class HelpCommand : public Commande {
public:
    HelpCommand() : Commande("help", { "-h" }, 0, "Display help information", false, true) {}

    void affecterArguments(const std::vector<std::string>& args) {
        // No arguments for help command
    }

    void lancerFonction()  {
        // Display help information for all commands and exit
        for (const auto& command : commandes) {
            std::cout << "Command: " << command->getName() << std::endl;
            std::cout << "Aliases: ";
            for (const auto& alias : command->getAliases()) {
                std::cout << alias << " ";
            }
            std::cout << std::endl;
            std::cout << "Description: " << command->getDescription() << std::endl;
            std::cout << "Arguments: " << command->getNumArgs() << std::endl;
            std::cout << std::endl;
        }
    }
};

