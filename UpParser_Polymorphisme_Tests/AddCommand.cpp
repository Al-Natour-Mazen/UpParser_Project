#include "pch.h"
#include "AddCommand.h"
#include <iostream>

AddCommand::AddCommand() : Command("Add", { "-add" }, 2, "add [args]", false, false), number1(0), number2(0) {}

void AddCommand::processArgs(const std::vector<std::string>& args) {
    try {
        number1 = std::stoi(args[0]);
        number2 = std::stoi(args[1]);
    }
    catch (std::invalid_argument& e) {
        throw std::runtime_error("Les arguments doivent être des nombres valides.");
    }
}

void AddCommand::execute() {
    int sum = number1 + number2;
    std::cout << "La somme est " << sum << std::endl;
}
