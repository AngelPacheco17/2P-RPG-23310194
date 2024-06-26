#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player: public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
private:
    int level;
    int experience;

    void levelUp();
    void saveProgress();
public:
    Player(char _name[], int _health, int maxHealth, int _attack, int _defense, int _speed);
    Player(char _name[], int _health, int maxHealth, int _attack, int _defense, int _speed, bool isPlayer, int level, int experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);
    char* serialize();
    static Player* unserialize(char* buffer);

    void gainExperience(int exp);

    static const unsigned int BUFFER_SIZE = sizeof(name) + sizeof (health) + sizeof(attack) + sizeof(maxHealth) + sizeof(defense) + sizeof(maxDefense) + sizeof(speed) + sizeof(isPlayer) + sizeof(defenseActive) + sizeof(level) + sizeof(experience);


    //TODO: Implement use object

private:
    char buffer[Player::BUFFER_SIZE];
};


#endif //RPG_PLAYER_H
