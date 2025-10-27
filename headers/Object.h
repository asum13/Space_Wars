#pragma once
#include <Headers/Vector2d.h>
#include <raylib.h>


class Object
{
public:

    Vector2d position = {0, 0};
    Vector2d velocity = {0,0};

    float size = 60.f;
    float friction = 2.2f;
    float speedCap = 1200.f;
    float borderOffset = 45.f;

    int objectType = 0; // 0: Iceberg, 1: Treasure, 2: Extra Life

    Color mainColor = PINK;

    void ApplyWind(Vector2d windDirection, float windStrength);

    void DrawAsCircle();

    void UpdatePhysics();

    void Warp();

    Vector2d Bounce(Object);

    bool CircleCollision(Object);
};
