#pragma once
#include <raylib.h>
#include <src/Vector2d.h>

class Player
{
public:

    Vector2d position = { 0,0 };
    Vector2d velocity = { 0, 0 };
    
    float size = 40.f;
    float friction = 2.f; //Slows the player down the higher it is
    float acceleration = 30.f; // Influences how fast velocity increases/decreases
    float turnSpeed = 3.f; //How fast player turns

    Vector2d windDirection = {-1,0};
    float windStrength = 1500.f;

    float angle = 0.f;
    Vector2d direction = { 1, 0 }; // Normalized Vector showing where the player is looking. should be {1,0} when angle = 0.
    
    Color shipColor = DARKGREEN;
    Color sailColor = WHITE;

    void Draw();

    void CheckInput();

    void Update();
};

