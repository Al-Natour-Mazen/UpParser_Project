#include "pch.h"
#include "Toto.h"
#include <iostream>

Toto::Toto() : Command("TOTO", { "-toto" }, 0, "Print 'Toto Tata Titi !'", false, true) {}

void Toto::processArgs(const std::vector<std::string>& args) {}

void Toto::execute() {
    executionTime = std::chrono::steady_clock::now();
    std::cout << "Toto Tata Titi !" << std::endl;
}
