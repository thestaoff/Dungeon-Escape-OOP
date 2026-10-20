#ifndef ENEMY_H
#define ENEMY_H

#include <algorithm>
#include <string>

class Enemy {
private:
    std::string name;
    int health;
    int damage;

public:
    Enemy(const std::string& enemyName, int enemyHealth, int enemyDamage)
        : name(enemyName), health(enemyHealth), damage(enemyDamage) {}

    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }

    void takeDamage(int amount) {
        health = std::max(0, health - amount);
    }

    bool isDefeated() const { return health <= 0; }
};

#endif
