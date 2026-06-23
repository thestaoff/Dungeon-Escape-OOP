#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

#include "Dungeon.h"
#include "Player.h"

class Game {
private:
    Player* player;
    Dungeon* dungeon;
    bool gameOver;

    int readChoice() const {
        int choice;
        while (!(std::cin >> choice)) {
            std::cout << "Please enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return choice;
    }

    void checkMoves() {
        if (!player->hasMovesLeft()) {
            std::cout << "You've run out of moves! You are trapped in the dungeon forever.\n";
            gameOver = true;
        }
    }

public:
    Game() : player(nullptr), dungeon(nullptr), gameOver(false) {}

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    ~Game() {
        delete player;
        delete dungeon;
    }

    void initialize() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        std::string playerName;
        std::cout << "Welcome to Dungeon Escape!\n";
        std::cout << "Enter your name: ";
        std::getline(std::cin, playerName);

        if (playerName.empty()) {
            playerName = "Adventurer";
        }

        player = new Player(playerName, 100, 15, 20);
        dungeon = new Dungeon();
        createDungeon();

        std::cout << "\nYou wake up in a dark dungeon. Your goal is to find the exit before running out of moves.\n";
        std::cout << "You have " << player->getMoves() << " moves to escape. Good luck, "
                  << player->getName() << "!\n\n";
    }

    void createDungeon() {
        dungeon->addRoom("Droplets of water echo from the moist stone walls around you.");
        dungeon->addRoom("Long shadows stretch across a flame-lit passageway.");
        dungeon->addRoom("A small room contains rusty chains hanging from the ceiling.");
        dungeon->addRoom("Old symbols are etched into the floor beneath your feet.");
        dungeon->addRoom("A narrow passageway is covered with cobwebs.");
        dungeon->addRoom("Broken pillars stand throughout a wide hall.");
        dungeon->addRoom("A strange glowing fountain stands in the center of the room.");
        dungeon->addRoom("A gloomy chamber smells strongly of damp stone.");
        dungeon->addRoom("Sunlight seeps through a fissure in the ceiling.");
        dungeon->addRoom("A massive wooden door stands on the far wall.", true);
        dungeon->populateDungeon();
    }

    void displayStatus() const {
        std::cout << "\n--- Status ---\n";
        std::cout << "Health: " << player->getHealth() << " | Attack: " << player->getAttack() << '\n';
        std::cout << "Moves left: " << player->getMoves() << " | Score: " << player->getScore() << '\n';
        player->displayInventory();
        std::cout << "--------------\n\n";
    }

    void displayRoom() const {
        Room* currentRoom = dungeon->getCurrentRoom();
        std::cout << "You are in: " << currentRoom->getDescription() << '\n';

        if (currentRoom->getIsExit()) {
            std::cout << "You found the exit!\n";
        }
        if (currentRoom->hasTreasure()) {
            std::cout << "There is treasure in this room!\n";
        }
        if (currentRoom->hasEnemy()) {
            std::cout << "A " << currentRoom->getEnemy()->getName() << " is guarding this room!\n";
        }
        if (currentRoom->containsChallenge()) {
            std::cout << "There is a challenge in this room!\n";
        }
    }

    void handlePlayerAction() {
        Room* currentRoom = dungeon->getCurrentRoom();

        if (currentRoom->getIsExit()) {
            std::cout << "Congratulations! You've escaped the dungeon!\n";
            gameOver = true;
            return;
        }

        if (currentRoom->hasEnemy()) {
            handleCombat();
            if (gameOver) {
                return;
            }
        }

        if (currentRoom->hasTreasure()) {
            handleTreasure();
        }

        if (currentRoom->containsChallenge()) {
            handleChallenge();
            if (gameOver) {
                return;
            }
        }

        displayOptions();
        std::cout << "What would you like to do? ";
        const int choice = readChoice();
        player->decreaseMoves();

        switch (choice) {
            case 1:
                if (dungeon->moveToNextRoom()) {
                    std::cout << "You move to the next room.\n";
                } else {
                    std::cout << "There is no way forward from here.\n";
                }
                break;
            case 2:
                if (dungeon->backtrack()) {
                    std::cout << "You backtrack to the previous room.\n";
                } else {
                    std::cout << "You cannot go back any further.\n";
                }
                break;
            case 3:
                player->heal(10);
                std::cout << "You rest for a moment and recover 10 health.\n";
                break;
            default:
                std::cout << "Invalid choice. You waste a move.\n";
                break;
        }

        checkMoves();
    }

    void handleCombat() {
        Enemy* enemy = dungeon->getCurrentRoom()->getEnemy();
        std::cout << "A " << enemy->getName() << " attacks you!\n";

        while (!enemy->isDefeated() && player->isAlive()) {
            std::cout << "\n--- Combat ---\n";
            std::cout << "Your health: " << player->getHealth() << " | " << enemy->getName()
                      << " health: " << enemy->getHealth() << '\n';
            std::cout << "1. Attack\n2. Try to flee (costs a move)\n";
            std::cout << "What would you like to do? ";
            const int choice = readChoice();

            if (choice == 1) {
                const int playerDamage = player->getAttack() + (std::rand() % 6);
                std::cout << "You attack the " << enemy->getName() << " for " << playerDamage << " damage!\n";
                enemy->takeDamage(playerDamage);

                if (!enemy->isDefeated()) {
                    const int enemyDamage = enemy->getDamage() + (std::rand() % 4);
                    std::cout << "The " << enemy->getName() << " attacks you for " << enemyDamage << " damage!\n";
                    player->takeDamage(enemyDamage);
                }
            } else if (choice == 2) {
                player->decreaseMoves();
                if (std::rand() % 2 == 0) {
                    std::cout << "You successfully flee from combat!\n";
                    checkMoves();
                    return;
                }

                const int enemyDamage = enemy->getDamage() + (std::rand() % 4);
                std::cout << "You failed to flee! The " << enemy->getName() << " attacks you for "
                          << enemyDamage << " damage!\n";
                player->takeDamage(enemyDamage);
            } else {
                const int enemyDamage = enemy->getDamage() + (std::rand() % 4);
                std::cout << "Invalid choice. The enemy attacks you for " << enemyDamage << " damage!\n";
                player->takeDamage(enemyDamage);
            }

            checkMoves();
            if (gameOver) {
                return;
            }
        }

        if (enemy->isDefeated()) {
            std::cout << "You defeated the " << enemy->getName() << "!\n";
            player->increaseScore(20);
            player->increaseAttack(1);
        } else if (!player->isAlive()) {
            std::cout << "You were defeated by the " << enemy->getName() << "!\n";
            gameOver = true;
        }
    }

    void handleTreasure() {
        Room* currentRoom = dungeon->getCurrentRoom();
        std::cout << "You found a treasure!\n1. Collect it\n2. Leave it\n";
        std::cout << "What would you like to do? ";
        const int choice = readChoice();

        if (choice == 1) {
            Treasure* treasure = currentRoom->collectTreasure();
            std::cout << "You collected a " << treasure->getName() << " worth "
                      << treasure->getValue() << " points!\n";
            player->increaseScore(treasure->getValue());
            player->addToInventory(treasure);
        } else {
            std::cout << "You decided to leave the treasure.\n";
        }
    }

    void handleChallenge() {
        Room* currentRoom = dungeon->getCurrentRoom();
        std::cout << dungeon->getChallenge() << '\n';
        std::cout << "1. Attempt to solve the challenge\n2. Skip the challenge (costs a move)\n";
        std::cout << "What would you like to do? ";
        const int choice = readChoice();

        if (choice == 1) {
            if (std::rand() % 2 == 0) {
                std::cout << "You successfully solved the challenge!\n";
                player->increaseScore(15);
                const int reward = std::rand() % 3;

                if (reward == 0) {
                    player->increaseAttack(2);
                    std::cout << "Your attack increased by 2!\n";
                } else if (reward == 1) {
                    player->heal(15);
                    std::cout << "You recovered 15 health!\n";
                } else {
                    Treasure* treasure = new Treasure("Mysterious Artifact", 15);
                    player->addToInventory(treasure);
                    player->increaseScore(treasure->getValue());
                    std::cout << "You found a Mysterious Artifact!\n";
                }
            } else {
                std::cout << "You failed to solve the challenge and take 10 damage from a trap!\n";
                player->takeDamage(10);
                if (!player->isAlive()) {
                    std::cout << "The trap was deadly! You have died.\n";
                    gameOver = true;
                }
            }
        } else {
            std::cout << "You decided to skip the challenge.\n";
            player->decreaseMoves();
            checkMoves();
        }

        currentRoom->completeChallenge();
    }

    void displayOptions() const {
        std::cout << "\nAvailable actions:\n";
        std::cout << "1. Move forward\n";
        std::cout << "2. Backtrack\n";
        std::cout << "3. Rest (recover health)\n";
    }

    bool isGameOver() const { return gameOver; }

    void displayGameOver() const {
        std::cout << "\n--- Game Over ---\n";
        std::cout << "Player: " << player->getName() << '\n';
        std::cout << "Final Score: " << player->getScore() << '\n';

        if (player->isAlive() && dungeon->getCurrentRoom()->getIsExit()) {
            std::cout << "Congratulations! You escaped the dungeon!\n";
        } else if (!player->isAlive()) {
            std::cout << "You died in the dungeon.\n";
        } else {
            std::cout << "You got trapped in the dungeon.\n";
        }
    }

    void run() {
        initialize();
        while (!isGameOver()) {
            displayStatus();
            displayRoom();
            handlePlayerAction();
        }
        displayGameOver();
    }
};

#endif
