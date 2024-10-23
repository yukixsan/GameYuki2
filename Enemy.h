#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

class Enemy {
private:
    Texture2D texture;
    Vector2 position;
    float speed;

public:
    Enemy(const char* textureFile, float startX, float startY, float moveSpeed);
    ~Enemy();
    void Move();
    void Draw();
    bool IsOffScreen();
    Vector2 GetPosition();
    float GetTextureWidth();  // Return the texture's width
    float GetTextureHeight(); // Return the texture's height

};

#endif
