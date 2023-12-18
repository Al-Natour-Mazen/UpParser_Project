#pragma once

#include "Commande.h"
#include "Parsing.h"

class HelpCommand : public Command {
public:
    HelpCommand(Parsing* parsToAdd);

    void processArgs(const std::vector<std::string>& args) override;

    void execute() override;

    void setParsing(Parsing* parsing);

private:
    Parsing* parsing;
};

