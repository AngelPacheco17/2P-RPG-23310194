#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>

using namespace std;

class Character {
protected:
    char name[30];
    int health;
    int attack;
    int maxHealth;
    int defense;
    int maxDefense;
    int speed;
    bool isPlayer;
    bool defenseActive = false;
public:
    Character(char _name[], int _health, int maxHealth, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual

    bool flee(Character* target);
    string toString();
    bool getIsPlayer();

    int getHealth();
    void upHealth(int newStat);
    int getMaxHealth();
    void upMaxHealth(int newStat);

    int getAttack();
    void upAttack(int newStat);

    int getDefense();
    void upDefense(int newStat);
    void defend();
    void finishDefend();
    void upMaxDefense(int newStat);

    int getSpeed();
    void upSpeed(int newStat);

};


#endif //RPG_CHARACTER_H
