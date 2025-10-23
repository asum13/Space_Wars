#include "Headers/Object.h"

void Object::ApplyWind(Vector2d windDirection, float windStrength)
{
    Vector2d windForce = windDirection.Normalize();
    windForce = windForce.Scale(windStrength * GetFrameTime());
    velocity = velocity.Add(windForce);
}

void Object::DrawAsCircle()
{
    DrawCircle(position.x, position.y, size, mainColor);
}


void Object::Warp()
{
    if (GetScreenWidth() + borderOffset < position.x)
    {
        position.x = - borderOffset;
    }
    if (- borderOffset > position.x)
    {
        position.x = GetScreenWidth() + borderOffset;
    }
    if (GetScreenHeight() + borderOffset < position.y)
    {
        position.y = -borderOffset;
    }
    if (-borderOffset > position.y)
    {
        position.y = GetScreenHeight() + borderOffset;
    }
}


void Object::Update()
{
    velocity.x -= velocity.x * friction * GetFrameTime();
    velocity.y -= velocity.y * friction * GetFrameTime();

    position = position.Add(velocity.Scale(GetFrameTime()));

    Warp();
}



bool Object::CircleCollision(Object targetObject)
{
    if (position.DistanceToTarget(targetObject.position) < size + targetObject.size)
    {
        return true;
    }
    return false;
}
