#include "GameManager.h"

GameManager::GameManager(Player* p, std::vector<Enemy*>& e) : player(p), enemies(e) {}

void GameManager::Update() {
    // Loop through all enemies and check for collisions
    for (int i = enemies.size() - 1; i >= 0; --i) {
        // Check for collision between player and enemy
        if (CheckCollisionRecs(
                { player->GetPosition().x, player->GetPosition().y, player->GetTextureWidth(), player->GetTextureHeight() },
                { enemies[i]->GetPosition().x, enemies[i]->GetPosition().y, enemies[i]->GetTextureWidth(), enemies[i]->GetTextureHeight() }
            )) {
            OnNotify(); // Notify that a collision happened
            delete enemies[i]; // Destroy enemy
            enemies.erase(enemies.begin() + i); // Remove from vector
        }
    }
}

void GameManager::OnNotify() {
    // Handle notification - for now, just remove the enemy
    // Additional logic can be added here, like increasing score or playing a sound effect
}
