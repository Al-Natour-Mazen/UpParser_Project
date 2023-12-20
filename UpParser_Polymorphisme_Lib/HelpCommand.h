#pragma once

#include "Command.h"
#include "Parsing.h"

class HelpCommand : public Command {
public:
    HelpCommand(Parsing* parsToAdd);

    void processArgs(const std::vector<std::string>& args) ;
    void execute() ;

    void setParsing(Parsing* parsing);
private:
    Parsing* parsing;
};

