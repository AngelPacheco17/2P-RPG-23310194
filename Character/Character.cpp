#include "Character.h"
#include <iostream>
#include <string.h>

using namespace std;

Character::Character(char _name[], int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    maxHealth = _maxHealth;
    attack = _attack;
    defense = _defense;
    maxDefense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::toString() {
    cout << "Name: " << name;
    return "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}

//----------------Health----------------

int Character::getHealth() {
    return health;
}
void Character::upHealth(int newStat){
    health += newStat;
}
void Character::upMaxHealth(int newStat) {
    maxHealth = newStat + maxHealth;
    cout<<name<<" has increased his health in: "<<newStat<<endl;
}
int Character::getMaxHealth() {
    return maxHealth;
}

//----------------Attack----------------
void Character::upAttack(int newStat) {
    attack = newStat + attack;
    cout<<name<<" has increased his attack in: "<<newStat<<endl;
}
int Character::getAttack() {
    return attack;
}

//----------------Defense----------------
void Character::upDefense(int newStat) {
    defense = newStat + defense;
}
int Character::getDefense() {
    return defense;
}
void Character::defend() {
    cout<<name<<" has increased his defense"<<endl;
    defenseActive = true;
    defense += (maxDefense * .2);
    cout<<"Defense: "<<defense<<endl;
}
void Character::finishDefend() {
    defense = maxDefense;
}
void Character::upMaxDefense(int newStat) {
    maxDefense = newStat + maxDefense;
    cout<<name<<" has increased his defense in: "<<newStat<<endl;
}

//----------------Speed----------------
void Character::upSpeed(int newStat) {
    speed = newStat + speed;
    cout<<name<<" has increased his speed in: "<<newStat<<endl;
}
int Character::getSpeed() {
    return speed;
}
