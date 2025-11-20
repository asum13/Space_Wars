#pragma once
#include <raylib.h>
#include <Headers/Vector2d.h>
#include <Headers/Object.h>

class Player: public Object
{
public:
    // Player variable values are decided in the SpawnPlayer function not here
    
    float acceleration = 35.f; // Influences how fast velocity increases/decreases
    float turnSpeed = 3.f; 

    Vector2d windDirection = {-1,0};
    float windStrength = 1500.f;

    float angle = 0.f;
    Vector2d direction = { 1, 0 }; // Normalized Vector showing where the player is looking. should be {1,0} at start.

    int lives = 3;
    float invincibilityTime = -0.1f;
    
    Color sailColor = WHITE;

    bool isAlive = true;

    void DrawPlayer();

    void CheckInput();

    void TurnToTarget(Vector2d target);

    void TakeDamage();

    void UpdatePlayer();
};

