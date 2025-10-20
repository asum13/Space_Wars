#pragma once
#include <raylib.h>
#include <src/Vector2d.h>

class Player
{
public:

    Vector2d position;
    Vector2d direction = { 1, 0 }; // Normalized Vector showing where the player is looking. Default Right
    Vector2d velocity = { 0, 0 };

    float offset = 0.3f;
    float size = 80.f;
    float angle = 0.f;
    float friction = 0.1f; //Lower the friction the more player is slowed down. At 1 frictionless, 0 player can't move.
	
    float acceleration = 10.f; // Influences how fast velocity increases/decreases
    float turnSpeed = 2.5f; //How fast player turns
    Color color = GREEN;

    void Draw();

    void CheckInput();

    void Update();
};

