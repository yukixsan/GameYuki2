#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
private:
    Texture2D texture;
    Vector2 position;
    float speed;
    float scale;
    float rotation;
    Rectangle collider;

public:
    Player(const char* textureFile, Vector2 startPos, float moveSpeed, float initialScale);
    ~Player();
    void Move();
    void Draw();
    void UpdateCollider();
    void Reset();
    Rectangle GetCollider();
    Vector2 GetPosition(); // Return the player's position
    float GetTextureWidth();  // Return the texture's width
    float GetTextureHeight(); // Return the texture's height

};

#endif
