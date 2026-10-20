#ifndef TREASURE_H
#define TREASURE_H

#include <string>

class Treasure {
private:
    std::string name;
    int value;

public:
    Treasure(const std::string& treasureName, int treasureValue)
        : name(treasureName), value(treasureValue) {}

    const std::string& getName() const { return name; }
    int getValue() const { return value; }
};

#endif
