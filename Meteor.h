#ifndef METEOR_H
#define METEOR_H

#include "raylib.h"
#include <string>

class Meteor {
public:
    Texture2D texture;
    Vector2 position;
    float speed;
    Rectangle MeteorCollider;

    Meteor(const std::string& texturePath, float startX, float startY, float moveSpeed, float colliderWidth, float colliderHeight);
    ~Meteor();
    
    void Move();                  // Update meteor position
    void Draw();                  // Draw the meteor
    void UpdateCollider();        // Update collider position based on meteor's position
    bool IsOffScreen();           // Check if the meteor has gone off screen
    Rectangle GetCollider();      // Return the collider rectangle
    Vector2 GetPosition();        // Return the position of the meteor
    float GetTextureWidth();      // Return the texture's width
    float GetTextureHeight();     // Return the texture's height
};

#endif 
