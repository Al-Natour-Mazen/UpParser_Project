#pragma once
#include <string>
#include <vector>

class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& aliases,
        int numArgs, const std::string& description, bool required, bool immediate);

    virtual ~Command() {}
   
    virtual void processArgs(const std::vector<std::string>& args) = 0;
    virtual void execute() = 0;

    const std::string& getName() const;
    int getNumArgs() const;
    bool isRequired() const;
    bool isImmediate() const;
    const std::vector<std::string>& getAliases() const;
    const std::string& getDescription() const;
    void setProcessed(bool value);
    bool isProcessed() const;

private:
    std::string name;
    std::vector<std::string> aliases;
    int numArgs;
    std::string description;
    bool required;
    bool immediate;
    bool processed;
};

