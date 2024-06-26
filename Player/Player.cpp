#include "Player.h"
#include <iostream>
#include "../Files/FileHandler.h"

using namespace std;

void Player::saveProgress(){
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    FileHandler().writeToFile("Info.data", buffer, Player::BUFFER_SIZE);

    cout << "\n----Saved----" << endl
    << "Stats:" << endl
    << this->toString() << endl;
}

Player::Player(char _name[], int _health, int _maxHealth, int _attack, int _defense, int _speed) : Character(_name, _health, _maxHealth, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(char *_name, int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_name, _health, _maxHealth, _attack, _defense, _speed, _isPlayer){
    level = _level;
    experience = _experience;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    if(trueDamage > 0){
        cout << name << " took " << trueDamage << " damage!" << endl;
        if(health <= 0) {
            cout << name << " has been defeated!" << endl;
        }
    } else {
        cout << name << " has defended the attack" << endl;
    }
}

void Player::levelUp() {
    level++;
    int opc;
    cout<<"\nYou've leveled up!"<<endl;
    cout<<"\nYour level is: "<<level<<endl;
    cout<<"Choose, which stat you prefere to increase?\n1.- Attack +3\n2.- Health +20\n3.- Defense +5\n4.- Speed +2"; cin>>opc;

    switch (opc){
        case 1:
            upAttack(3);
            break;
        case 2:
            upMaxHealth(20);
            upHealth(20);
            break;
        case 3:
            upMaxDefense(5);
            upDefense(5);
            break;
        case 4:
            upSpeed(2);
            break;
        default:
            break;
    }
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". ";
        possibleTargets[i]->printName();
    }
    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << "Select an action: " << endl
    << "1.- Attack" << endl
    << "2.- Defend" << endl
    << "3. Save the Game" << endl;
    cin >> action;

    //TODO: Validate input
    Action currentAction;
    Character* target = nullptr;

    finishDefend();

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target, enemies](){
                doAttack(target);
                if(target->getHealth()<=0){
                    Enemy* enemySelected = ((Enemy*)target);
                    if(enemySelected->getExperience() + experience >= 100){
                        for (int i = 0; i < enemies.size(); i++) {
                            if(enemies[i]->getId() != enemySelected->getId() && enemies.size() > 1) {
                                enemies[i]->upAttack(1);
                            }
                        }
                    }
                    gainExperience(enemySelected->getExperience());
                }
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.action = [this]() {
                defend();
            };
            currentAction.speed = getSpeed();
            break;
        case 3:
            saveProgress();
            return takeAction(enemies);
            break;
        default:
            cout << "Invalid action" << endl;
            return takeAction(enemies);
            break;

    }

    return currentAction;
}

char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &maxHealth, sizeof(maxHealth));
    iterator += sizeof(maxHealth);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &maxDefense, sizeof(maxDefense));
    iterator += sizeof(maxDefense);

    memcpy(iterator,&speed , sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &defenseActive, sizeof(defenseActive));
    iterator += sizeof(defenseActive);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

Player* Player::unserialize(char* buffer) {
    char* iterator = buffer;
    char name[30];
    int health, attack, maxHealth, defense, maxDefense, speed, level, experience;
    bool isPlayer, defenseActive;

    memcpy(&name, iterator, sizeof(name));
    iterator+=sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator+=sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator+=sizeof(attack);

    memcpy(&maxHealth, iterator, sizeof(maxHealth));
    iterator+=sizeof(maxHealth);

    memcpy(&defense, iterator, sizeof(defense));
    iterator+=sizeof(defense);

    memcpy(&maxDefense, iterator, sizeof(maxDefense));
    iterator+=sizeof(maxDefense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator+=sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator+=sizeof(isPlayer);

    memcpy(&defenseActive, iterator, sizeof(defenseActive));
    iterator+=sizeof(defenseActive);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, maxHealth, attack, defense, speed, isPlayer, level, experience);
}