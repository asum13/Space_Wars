#pragma once
#include <raylib.h>
#include <Headers/Vector2d.h>
#include <Headers/Object.h>

class Player: public Object
{
public:
    
    float acceleration = 30.f; // Influences how fast velocity increases/decreases
    float turnSpeed = 3.f; //How fast player turns

    Vector2d windDirection = {-1,0};
    float windStrength = 1500.f;

    float angle = 0.f;
    Vector2d direction = { 1, 0 }; // Normalized Vector showing where the player is looking. should be {1,0} when angle = 0.

    int lives = 3;
    float invincibilityTime = 0.f;
    
    Color sailColor = WHITE;

    bool isAlive = true;

    void DrawPlayer();

    void CheckInput();
};

