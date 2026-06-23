#ifndef DUNGEON_H
#define DUNGEON_H

#include <queue>
#include <stack>
#include <string>

#include "Room.h"

class Dungeon {
private:
    Room* head;
    Room* currentRoom;
    int roomCount;
    std::queue<std::string> challenges;
    std::stack<Room*> path;

public:
    Dungeon() : head(nullptr), currentRoom(nullptr), roomCount(0) {
        initializeChallenges();
    }

    Dungeon(const Dungeon&) = delete;
    Dungeon& operator=(const Dungeon&) = delete;

    ~Dungeon() {
        Room* current = head;
        while (current != nullptr) {
            Room* nextRoom = current->getNext();
            delete current;
            current = nextRoom;
        }
    }

    void initializeChallenges() {
        challenges.push("You find a riddle on the wall.");
        challenges.push("A locked chest sits in the corner. You need to find the combination.");
        challenges.push("The floor is covered with pressure plates. You must find the safe path.");
        challenges.push("A barrier blocks your way. You must find the correct way to break it.");
    }

    void addRoom(const std::string& description, bool isExit = false) {
        Room* newRoom = new Room(roomCount, description, isExit);

        if (head == nullptr) {
            head = newRoom;
            currentRoom = head;
        } else {
            Room* lastRoom = head;
            while (lastRoom->getNext() != nullptr) {
                lastRoom = lastRoom->getNext();
            }
            lastRoom->setNext(newRoom);
        }

        ++roomCount;
    }

    void populateDungeon() {
        Room* room = head;
        int index = 0;

        while (room != nullptr) {
            if (!room->getIsExit()) {
                if (index % 3 == 0) {
                    room->addEnemy("Dungeon Guardian", 25, 5);
                } else if (index % 3 == 1) {
                    room->addTreasure("Gold Brick", 10);
                } else {
                    room->setChallenge();
                }
            }
            room = room->getNext();
            ++index;
        }
    }

    Room* getCurrentRoom() const { return currentRoom; }

    bool moveToNextRoom() {
        if (currentRoom == nullptr || currentRoom->getNext() == nullptr) {
            return false;
        }

        path.push(currentRoom);
        currentRoom = currentRoom->getNext();
        return true;
    }

    bool backtrack() {
        if (path.empty()) {
            return false;
        }

        currentRoom = path.top();
        path.pop();
        return true;
    }

    std::string getChallenge() {
        if (challenges.empty()) {
            return "The room appears to be safe.";
        }

        std::string challenge = challenges.front();
        challenges.pop();
        return challenge;
    }
};

#endif
