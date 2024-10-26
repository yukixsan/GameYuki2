#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Observer.h"
#include "Player.h"
#include "Enemy.h"
#include "Meteor.h"
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class GameManager : public Observer {
private:
    Player* player;
    std::vector<Enemy*>& enemies; // Reference to the enemies in the game
    std::vector<Meteor*> meteors;

public:
    int score;
    bool isGamePaused = false;
    GameManager(Player* p, std::vector<Enemy*>& e,std::vector<Meteor*>& m);
    void Update(); // Game loop update function to check for collisions
    void UpdateMeteor();
    void OnNotify() override;
    void Draw();
    void DisplayScore();
    void PauseGame();
    void RestartGame(Player* player, std::vector<Enemy*>& enemies, std::vector<Meteor*>& meteors);

};

#endif
