#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Observer.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GameManager : public Observer {
private:
    Player* player;
    std::vector<Enemy*>& enemies; // Reference to the enemies in the game

public:
    GameManager(Player* p, std::vector<Enemy*>& e);
    void Update(); // Game loop update function to check for collisions
    void OnNotify() override; // Implementing the observer's notification
};

#endif
