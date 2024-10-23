#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "GameManager.h"
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

int main() {
    // Initialize the window
    InitWindow(1920, 1080, "SPACECRAFT CRASHER");
    ToggleFullscreen();
    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Create player object
    Player player("Textures/Asteroid.png", { 400, 300 }, 0.1f, 0.5f);

    // Container to store enemies
    std::vector<Enemy*> enemies;

    //Init gameManager
    GameManager gameManager(&player, enemies);

     // Spawning variables
    float spawnTimer = 0.0f; // Timer to track the time since last spawn
    int spawnInterval = 1;    // Randomized spawn interval (in seconds)
    const int maxEnemies = 1; // Only 1 enemy on screen at a time

    // Randomly pick the first spawn interval between 1, 2, and 3 seconds
    spawnInterval = rand() % 3 + 1;

    // Main game loop
    while (!WindowShouldClose()) {
        
        player.Move();
        spawnTimer += GetFrameTime();
        // Spawn new enemies if we have less than the max allowed
         if (enemies.size() < maxEnemies && spawnTimer >= spawnInterval) {
            // Random Y position within screen bounds (subtract 50 to keep it within the screen)
            float randomY = static_cast<float>(rand() % (GetScreenHeight() - 50));

            // Spawn a new enemy from the right
            enemies.push_back(new Enemy("Textures/spacecraft.png", GetScreenWidth(), randomY, 0.2f)); 

            // Reset the timer
            spawnTimer = 0.0f;

            // Randomize the next spawn interval (1, 2, or 3 seconds)
            spawnInterval = rand() % 3 + 1;
        }

        // Update enemy movement and remove if off-screen
        for (int i = enemies.size() - 1; i >= 0; --i) {
            enemies[i]->Move();

            // Remove and delete enemy if it goes off-screen
            if (enemies[i]->IsOffScreen()) {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
            }
        }

        //Check collison
        gameManager.Update();

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player
        player.Draw();

        // Draw enemies
        for (Enemy* enemy : enemies) {
            enemy->Draw();
        }

        EndDrawing();
    }

    // Clean up memory
    for (Enemy* enemy : enemies) {
        delete enemy;
    }

    CloseWindow();

    return 0;
}
