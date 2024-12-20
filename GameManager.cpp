#include "GameManager.h"

GameManager::GameManager(Player* p, std::vector<Enemy*>& e, std::vector<Meteor*>& m) : player(p), enemies(e),meteors(m), score(0) {}


void GameManager::Update(float deltaTime) {
    // Loop through all enemies and check for collisions
    for (auto it = enemies.begin(); it != enemies.end();) {
        (*it)->UpdateCollider(); 
        // Check for collision between player and enemy collider
        if (CheckCollisionRecs(player->GetCollider(), (*it)->collider)) {
explosions.emplace_back((*it)->GetPosition(),30,100);  // Update position if needed
        explosions[0].Emit();  // Emit particles            
        // Collision with Enemy: Destroy the enemy and increase 
            delete *it;
            it = enemies.erase(it);
            score++;
            continue;  // Continue to the next iteration since an enemy was erased
        } else {
            ++it;
        }
    }
    //Explosion
       for (auto it = explosions.begin(); it != explosions.end();) {
        it->Update(deltaTime);  // Update each particle system
        if (!it->IsActive()) {  // If the explosion is finished, remove it
            it = explosions.erase(it);
        } else {
            ++it;
        }
    }
}

void GameManager::UpdateMeteor() {

 //Check for meteor collision
    for (auto it = meteors.begin(); it != meteors.end();) 
    {       
        (*it)->UpdateCollider(); // Update each meteor's collider
        // Check for collision between player and meteor collider
        if (CheckCollisionRecs(player->GetCollider(), (*it)->MeteorCollider)) {
            // Player collides with Meteor
            delete *it;
            it = meteors.erase(it);
            //PauseGame();  // Call a function to pause the game
            continue;;  // Exit the loop since the player is destroyed
        } else {
            ++it;
        }
    }
}
void GameManager::DisplayScore()
{
    std::string scoreText = "Score: " + std::to_string(score);
    int screenWidth = GetScreenWidth();
    int fontSize = 40;
    int textWidth = MeasureText(scoreText.c_str(), fontSize);

    DrawText(scoreText.c_str(), (screenWidth - textWidth) / 2, 10, fontSize, WHITE);
}

void GameManager::PauseGame()
{
    isGamePaused = true;
}
void GameManager::RestartGame(Player* player, std::vector<Enemy*>& enemies, std::vector<Meteor*>& meteors)
{
    isGamePaused = false;
    score = 0;
    
    // Clear all dynamically allocated enemies and meteors
    for (Enemy* enemy : enemies) delete enemy;
    enemies.clear();
    for (Meteor* meteor : meteors) delete meteor;
    meteors.clear();
    explosions.clear();

    // Reset player properties, if necessary
    player->Reset();
}

void GameManager::Draw()
{
     for ( auto& explosion : explosions) {
        explosion.Draw();  // Draw each active explosion
    }
}

void GameManager::OnNotify()
{

}
