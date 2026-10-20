#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Treasure.h"

class Player {
private:
    std::string name;
    int health;
    int attack;
    int moves;
    int score;
    std::vector<Treasure*> inventory;

public:
    Player(const std::string& playerName, int playerHealth, int playerAttack, int playerMoves)
        : name(playerName), health(playerHealth), attack(playerAttack), moves(playerMoves), score(0) {}

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    ~Player() {
        for (Treasure* item : inventory) {
            delete item;
        }
    }

    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getMoves() const { return moves; }
    int getScore() const { return score; }

    void takeDamage(int amount) {
        health = std::max(0, health - amount);
    }

    void heal(int amount) {
        health = std::min(100, health + amount);
    }

    void increaseAttack(int amount) { attack += amount; }

    void decreaseMoves(int amount = 1) {
        moves = std::max(0, moves - amount);
    }

    void increaseScore(int amount) { score += amount; }

    bool isAlive() const { return health > 0; }
    bool hasMovesLeft() const { return moves > 0; }

    void addToInventory(Treasure* item) {
        if (item != nullptr) {
            inventory.push_back(item);
        }
    }

    void displayInventory() const {
        std::cout << "Inventory: ";
        if (inventory.empty()) {
            std::cout << "Empty\n";
            return;
        }

        for (std::size_t i = 0; i < inventory.size(); ++i) {
            std::cout << inventory[i]->getName();
            if (i + 1 < inventory.size()) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
};

#endif
