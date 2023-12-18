#pragma once
#include <string>

class Cible {

private:
	std::string description;
	bool peutEtreVide;

public:
    Cible(const std::string& description, bool canBeEmpty)
        : description(description), peutEtreVide(canBeEmpty) {}

    const std::string& getDescription() const { return description; }
    bool canBeEmpty() const { return canBeEmpty; }
};


