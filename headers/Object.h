#pragma once
#include <Headers/Vector2d.h>
#include <raylib.h>


class Object
{
public:

    Vector2d position = {0, 0};
    Vector2d velocity = {0,0};

    float size = 60.f;
    float friction = 1.5f;
    float borderOffset = 60.f;

    Color mainColor = PINK;

    void ApplyWind(Vector2d windDirection, float windStrength);

    void DrawAsCircle();

    void Update();

    void Warp();

    bool CircleCollision(Object);
};
