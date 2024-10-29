#include "Player.h"
    Vector2 initialPosition = {400, 300};

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

    rotation += 0.5f; // Adjust speed of rotation as needed
    if (rotation >= 360.0f) rotation = 0.0f; // Reset after full rotation
    
    UpdateCollider();

}

void Player::UpdateCollider()
{
    collider.x = position.x ;
    collider.y = position.y + (texture.height / 9.0f) - (collider.height / 9.0f);
}

void Player::Draw() {
   // DrawTextureEx(texture, position, rotation, scale, WHITE);
   
    Rectangle sourceRect = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle destRect = { position.x, position.y, texture.width * scale, texture.height * scale };

    // Calculate the center of the scaled texture
    Vector2 origin = { (texture.width * scale) / 2.0f, (texture.height * scale) / 2.0f };

    // Now, draw with rotation and scaling around the center
    DrawTexturePro(texture, sourceRect, destRect, origin, rotation, WHITE);

    //Collider
    collider.x = position.x - (collider.width / 2.0f);
    collider.y = position.y - (collider.height / 2.0f);
    float scaledWidth = texture.width * scale;
    float scaledHeight = texture.height * scale;
    collider.width = scaledWidth; collider.height = scaledHeight;
    DrawRectangleLines(static_cast<int>(collider.x), static_cast<int>(collider.y),
                       static_cast<int>(collider.width), static_cast<int>(collider.height), GREEN);
}
void Player::Reset()
{
    position = initialPosition;
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

