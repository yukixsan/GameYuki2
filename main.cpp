#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "Meteor.h"
#include "GameManager.h"
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

//For stars
#define WIDTH 1920
#define HEIGHT 1080
#define STARS 200
#define SCROLL_SPEED 12
typedef struct 
{
    float x, y, z;
        
}Star;
float randf() {
    return (rand() % 1000) / 1000.0f;
}

int main() {
    // Initialize the window
    InitWindow(1920, 1080, "SPACECRAFT CRASHER");
    ToggleFullscreen();
    SetTargetFPS(60);
    //Star generation
    Star stars[STARS] = {0};
    //-----RANDOMISE THE STARS POSITIONS-----//
    for (int i = 0; i < STARS; i++) { 
        stars[i].x = GetRandomValue(0, WIDTH);
        stars[i].y = GetRandomValue(0, HEIGHT);
        stars[i].z = randf();
    }

    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Create player object
    Player player("Textures/Asteroid.png", { 400, 300 }, 10.0f, 0.5f);

    // Container to store enemies
    std::vector<Enemy*> enemies;
    std::vector<Meteor*> meteors;

    //Init gameManager
    GameManager gameManager(&player, enemies, meteors);

     // Spawning variables
    float spawnTimer = 0.0f; // Timer to track the time since last spawn
    int spawnInterval = 1;    // Randomized spawn interval (in seconds)
    const int maxEnemies = 1; // Only 1 enemy on screen at a time
    const int maxMeteors = 2;
    float meteorSpawnTimer = 0.0f;
    float meteorSpawnInterval = static_cast<float>(rand() % 3 + 3);

    // Randomly pick the first spawn interval between 1, 2, and 3 seconds
    spawnInterval = rand() % 3 + 1;

    // Main game loop
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            gameManager.RestartGame(&player, enemies, meteors);
        }
        //-----SCROLL THE STARS-----//
        for (int i = 0; i < STARS; i++) {
            stars[i].x -= SCROLL_SPEED * (stars[i].z / 1);
 
            if (stars[i].x <= 0) {  // Check if the star has gone off screen
                stars[i].x += WIDTH;
                stars[i].y = GetRandomValue(0, HEIGHT);
            }
        }
        
        player.Move();
        spawnTimer += GetFrameTime();
        meteorSpawnTimer += GetFrameTime();
        // Spawn new enemies if we have less than the max allowed
         if (enemies.size() < maxEnemies && spawnTimer >= spawnInterval) {
            // Random Y position within screen bounds (subtract 50 to keep it within the screen)
            float randomY = static_cast<float>(rand() % (GetScreenHeight() - 120));
            // Spawn a new enemy from the right
            enemies.push_back(new Enemy("Textures/spacecraft.png", GetScreenWidth(), randomY, 15.0f, 400.0f, 100.0f)); 

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
        //Spawn Meteor
         if (meteors.size() < maxMeteors && meteorSpawnTimer >= meteorSpawnInterval) {
            // Random Y position within screen bounds (subtract 50 to keep it within the screen)
            float randomY = static_cast<float>(rand() % (GetScreenHeight() - 150));

            // Spawn a new enemy from the right
            meteors.push_back(new Meteor("Textures/MeteorLawan.png", GetScreenWidth(), randomY, 9.0f, 250.0f, 180.0f)); 

            // Reset the timer
            meteorSpawnTimer = 0.0f;
            meteorSpawnInterval = rand() % 3 + 3;
        }

        // Update enemy movement and remove if off-screen
        for (int i = meteors.size() - 1; i >= 0; --i) {
            meteors[i]->Move();
            meteors[i]->UpdateCollider();

            // Remove and delete enemy if it goes off-screen
            if (meteors[i]->IsOffScreen()) {
                delete meteors[i];
                meteors.erase(meteors.begin() + i);
            }
        }

        //Check collison
        gameManager.Update();
         for (auto it = meteors.begin(); it != meteors.end();) 
    {       
        (*it)->UpdateCollider(); // Update each meteor's collider
        // Check for collision between player and meteor collider
        if (CheckCollisionRecs(player.GetCollider(), (*it)->MeteorCollider)) {
            // Player collides with Meteor
            gameManager.PauseGame();  // Call a function to pause the game
            break;  // Exit the loop since the player is destroyed
        } else {
            ++it;
        }
    }
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
    if (!gameManager.isGamePaused)
    {
    // Draw stars
        for (int i = 0; i < STARS; i++) {
                float x = stars[i].x;
                float y = stars[i].y;
                
                DrawPixel(x, y, WHITE);
            }
        // Draw player
        player.Draw();
        gameManager.DisplayScore();
        // Draw enemies
        for (Enemy* enemy : enemies) {
            enemy->Draw();
        }
        for (Meteor* meteors : meteors) {
            meteors->Draw();
        }
    }
    else
    {
       const char* loseText = "You Lose";
        int loseFontSize = 90;
        int loseTextWidth = MeasureText(loseText, loseFontSize);

        // Center the "You Lose" text
        DrawText(loseText, (GetScreenWidth() - loseTextWidth) / 2, GetScreenHeight() / 2 - loseFontSize, loseFontSize, RED);

        const char* restartText = "Press R to restart";
        int restartFontSize = 40;
        int restartTextWidth = MeasureText(restartText, restartFontSize);

        // Center the "Press R to restart" text below "You Lose"
        DrawText(restartText, (GetScreenWidth() - restartTextWidth) / 2, GetScreenHeight() / 2 + loseFontSize / 2, restartFontSize, WHITE);
    }
        EndDrawing();
    }

    // Clean up memory
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    for (Meteor* meteors : meteors) {
        delete meteors;
    }

    CloseWindow();

    return 0;
}
