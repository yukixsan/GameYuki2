#include "Enemy.h"

Enemy::Enemy(const char* textureFile, float startX, float startY, float moveSpeed) {
    texture = LoadTexture(textureFile);
    position = { startX, startY };
    speed = moveSpeed;
}

Enemy::~Enemy() {
    UnloadTexture(texture);
}

void Enemy::Move() {
    position.x -= speed;
}

void Enemy::Draw() {
    DrawTextureEx(texture, position, 0.0f, 0.5f, WHITE); // Assuming no scaling
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