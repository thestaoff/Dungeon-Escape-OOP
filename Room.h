#ifndef ROOM_H
#define ROOM_H

#include <string>

#include "Enemy.h"
#include "Treasure.h"

class Room {
private:
    int id;
    std::string description;
    Treasure* treasure;
    Enemy* enemy;
    bool hasChallenge;
    bool isExit;
    Room* next;

public:
    Room(int roomId, const std::string& roomDescription, bool exitRoom = false)
        : id(roomId),
          description(roomDescription),
          treasure(nullptr),
          enemy(nullptr),
          hasChallenge(false),
          isExit(exitRoom),
          next(nullptr) {}

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    ~Room() {
        delete treasure;
        delete enemy;
    }

    int getId() const { return id; }
    const std::string& getDescription() const { return description; }
    Room* getNext() const { return next; }
    bool getIsExit() const { return isExit; }

    void setNext(Room* nextRoom) { next = nextRoom; }

    void addTreasure(const std::string& name, int value) {
        delete treasure;
        treasure = new Treasure(name, value);
    }

    void addEnemy(const std::string& name, int health, int damage) {
        delete enemy;
        enemy = new Enemy(name, health, damage);
    }

    void setChallenge() { hasChallenge = true; }
    void completeChallenge() { hasChallenge = false; }

    bool hasTreasure() const { return treasure != nullptr; }
    bool hasEnemy() const { return enemy != nullptr && !enemy->isDefeated(); }
    bool containsChallenge() const { return hasChallenge; }

    Treasure* collectTreasure() {
        Treasure* collectedTreasure = treasure;
        treasure = nullptr;
        return collectedTreasure;
    }

    Enemy* getEnemy() const { return enemy; }
};

#endif
