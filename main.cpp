//Jose Angel Pacheco Cervantes
//23310194
//2°P

#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"


int main() {
    Player *player = new Player("Victor", 50, 8, 10, 3);
    Enemy *enemy = new Enemy("Goblin", 15, 12, 5, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 20, 15, 5, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
