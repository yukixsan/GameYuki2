#include "Player.h"

Player::Player(const char* textureFile, Vector2 startPos, float moveSpeed, float initialscale) {
    texture = LoadTexture(textureFile);
    position = startPos;
    speed = moveSpeed;
    scale = initialscale;
}

Player::~Player() {
    UnloadTexture(texture);
}

void Player::Move() {
    float playerWidth = texture.width * scale;
    float playerHeight = texture.height * scale;

    if (IsKeyDown(KEY_W) && position.y > 0) {
        position.y -= speed;
    }
    if (IsKeyDown(KEY_S) && position.y < GetScreenHeight() - playerHeight) {
        position.y += speed;
    }
    if (IsKeyDown(KEY_A) && position.x > 0) {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_D) && position.x < GetScreenWidth() - playerWidth) {
        position.x += speed;
    }
}

void Player::Draw() {
    DrawTextureEx(texture, position, 0.0, scale, WHITE);
}
Vector2 Player::GetPosition() {
    return position;
}

float Player::GetTextureWidth() {
    return texture.width * scale; // Account for scaling
}

float Player::GetTextureHeight() {
    return texture.height * scale; // Account for scaling
}

