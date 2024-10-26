#include "Player.h"

Player::Player(const char* textureFile, Vector2 startPos, float moveSpeed, float initialscale) {
    texture = LoadTexture(textureFile);
    position = startPos;
    speed = moveSpeed;
    scale = initialscale;

    collider.width = 220.0f;  // Adjust this value as needed
    collider.height = 160.0f; // Adjust this value as needed
    collider.x = position.x + (texture.width / 2.0f) - (collider.width / 2.0f);
    collider.y = position.y+ (texture.height / 2.0f) - (collider.height / 2.0f);
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
        UpdateCollider();

}

void Player::UpdateCollider()
{
    collider.x = position.x ;
    collider.y = position.y + (texture.height / 9.0f) - (collider.height / 9.0f);
}

void Player::Draw() {
    DrawTextureEx(texture, position, 0.0, scale, WHITE);
    DrawRectangleLines(static_cast<int>(collider.x), static_cast<int>(collider.y),
                       static_cast<int>(collider.width), static_cast<int>(collider.height), GREEN);
}
Vector2 Player::GetPosition() {
    return position;
}

Rectangle Player::GetCollider() {
    return collider;
}


float Player::GetTextureWidth() {
    return texture.width * scale; // Account for scaling
}

float Player::GetTextureHeight() {
    return texture.height * scale; // Account for scaling
}

