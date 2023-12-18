#pragma once

#include <string>
#include <vector>
#include "Commande.h"
#include "Cible.h"

class Parsing {

private:
    std::vector<Commande*> commands;
    Cible* cible;
    std::string ligneCommande;

public:
    Parsing() {}

    void parseCommandLine(const std::vector<std::string>& commandLine);
    void addCommand(Commande* command);
    void addTarget(Cible* target);

};


