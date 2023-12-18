#pragma once
#include <string>
#include <vector>


#pragma once
#include <string>
#include <vector>


class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& aliases,
        int numArgs, const std::string& description, bool required, bool immediate)
        : name(name), aliases(aliases), numArgs(numArgs),
        description(description), required(required), immediate(immediate) {}

    virtual ~Command() {}

    const std::string& getName() const { return name; }

    bool match(const std::string& arg) const {
        // Check if the argument matches the command or any of its aliases
        if (arg == name || std::find(aliases.begin(), aliases.end(), arg) != aliases.end()) {
            return true;
        }
        return false;
    }

    virtual void processArgs(const std::vector<std::string>& args) = 0;
    virtual void execute() = 0;
private:
    std::string name;
    std::vector<std::string> aliases;
    int numArgs;
    std::string description;
    bool required;
    bool immediate;
};

