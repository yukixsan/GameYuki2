#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <string>
class Enemy {
public:
    Texture2D texture;
    Vector2 position;
    float speed;
    Rectangle collider;

    Enemy(const std::string& texturePath, float startX, float startY, float moveSpeed, float colliderWidth, float colliderHeight);
    ~Enemy();
    void Move();
     void Draw();
     void UpdateCollider();
    bool IsOffScreen();
    Vector2 GetPosition();
    float GetTextureWidth();  // Return the texture's width
    float GetTextureHeight(); // Return the texture's height

};

#endif
