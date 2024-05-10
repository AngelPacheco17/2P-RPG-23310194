#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

using namespace std;

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("Info.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        char nombre[30];
        cout<<"Enter your nickname:\n"; cin.getline(nombre, 30, '\n');
        return new Player(nombre, 50, 50, 8, 10, 3);
    }
}

int main() {

    Player *player = loadPlayerInfo();
    Enemy *enemy = new Enemy("Goblin", 15, 15, 12, 5, 5, 120, 0);
    Enemy *enemy2 = new Enemy("Orc", 20, 20, 15, 6, 5, 150, 1);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();
    
    delete player;
    delete enemy;
    delete enemy2;
    delete combat;
    try{
        remove("Info.data");
        cout<<"The file has been deleted to start a new game";
    } catch (int error){

    }
    return 0;
}

//g++ main.cpp Player/Player.cpp Enemy/Enemy.cpp Combat/Combat.cpp Combat/Action.cpp Character/Character.cpp Files/FileHandler.cpp -o main ; ./main.exe