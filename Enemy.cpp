#include "Enemy.h"

Enemy::Enemy(const std::string& texturePath, float startX, float startY, float moveSpeed, float colliderWidth, float colliderHeight) {
    texture = LoadTexture(texturePath.c_str());
    position = { startX, startY };
    speed = moveSpeed;
    collider.width = colliderWidth;
    collider.height = colliderHeight;
    collider.x = position.x + (texture.width / 2.0f) - (collider.width / 2.0f);
    collider.y = position.y + (texture.height / 2.0f) - (collider.height / 2.0f);}

Enemy::~Enemy() {
    UnloadTexture(texture);
}

void Enemy::Move() {
    position.x -= speed;

    UpdateCollider();
}

void Enemy::Draw() {
    DrawTextureEx(texture, position, 0.0f, 0.5f, WHITE); // Assuming no scaling
    DrawRectangleLines(static_cast<int>(collider.x), static_cast<int>(collider.y),
                       static_cast<int>(collider.width), static_cast<int>(collider.height), GREEN);
}

void Enemy::UpdateCollider()
{
    collider.x = position.x ;
    collider.y = position.y + (texture.height / 4.0f) - (collider.height / 4.0f);
}

bool Enemy::IsOffScreen() {
    return position.x + texture.width < 0;
}

Vector2 Enemy::GetPosition() {
    return position;
}

float Enemy::GetTextureWidth() {
    return texture.width;
}

float Enemy::GetTextureHeight() {
    return texture.height;
}