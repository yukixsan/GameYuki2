#include "Meteor.h"

Meteor::Meteor(const std::string& textureFile, float startX, float startY, float moveSpeed, float colliderWidth, float colliderHeight) 
{
    texture = LoadTexture(textureFile.c_str());
    position = { startX, startY };
    speed = moveSpeed;
    MeteorCollider.height = colliderHeight;
    MeteorCollider.width = colliderWidth;
    MeteorCollider.x = position.x + (texture.width / 2.0f) - (MeteorCollider.width / 2.0f);
    MeteorCollider.y = position.y + (texture.height / 2.0f) - (MeteorCollider.height / 2.0f);
}
Meteor::~Meteor()
{
        UnloadTexture(texture);

}
void Meteor::Move() {
    position.x -= speed; // Move left
    UpdateCollider(); // Update the collider position
}
void Meteor::UpdateCollider() 
{
    MeteorCollider.x = position.x ;
    MeteorCollider.y = position.y + (texture.height / 25.0f) - (MeteorCollider.height / 25.0f);
}
void Meteor::Draw() {
    DrawTextureEx(texture, position, 0.0f, 0.5f, WHITE); // Assuming no scaling
    DrawRectangleLines(static_cast<int>(MeteorCollider.x), static_cast<int>(MeteorCollider.y),
                       static_cast<int>(MeteorCollider.width), static_cast<int>(MeteorCollider.height), RED);
}
bool Meteor::IsOffScreen() {
    return position.x + texture.width < 0;
}
Rectangle Meteor::GetCollider()
{
    return MeteorCollider;
}
Vector2 Meteor::GetPosition() {
    return position;
}

float Meteor::GetTextureWidth() {
    return texture.width;
}

float Meteor::GetTextureHeight() {
    return texture.height;
}