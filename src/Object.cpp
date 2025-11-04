#include "Headers/Object.h"
#include <iostream>

using namespace std;

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


void Object::UpdatePhysics()
{
    if (velocity.GetMagnitude() > speedCap)
    {
        velocity.Normalize();
        velocity.Scale(speedCap);
    }
    
    velocity.x -= velocity.x * friction * GetFrameTime();
    velocity.y -= velocity.y * friction * GetFrameTime();
    
    position = position.Add(velocity.Scale(GetFrameTime()));

    Warp();
}

Vector2d Object::Bounce(Object otherObject)
{
    Vector2d thisOffset;
    Vector2d otherOffset;

    float force = otherObject.velocity.Subtract(velocity).GetMagnitude();

    thisOffset = position.Subtract(otherObject.position).Normalize().Scale(force/otherObject.size * 60);
    otherOffset = otherObject.position.Subtract(position).Normalize().Scale(force/size * 60);
    
    velocity = velocity.Add(thisOffset);

    return otherOffset;
}




bool Object::CircleCollision(Object targetObject)
{
    if (position.DistanceToTarget(targetObject.position) < size + targetObject.size)
    {
        return true;
    }
    return false;
}
