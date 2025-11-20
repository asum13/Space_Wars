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
    if (GetScreenWidth() + size < position.x)
    {
        position.x = - size;
    }
    if (- size > position.x)
    {
        position.x = GetScreenWidth() + size;
    }
    if (GetScreenHeight() + size < position.y)
    {
        position.y = -size;
    }
    if (-size > position.y)
    {
        position.y = GetScreenHeight() + size;
    }
}


void Object::UpdatePhysics()
{
    Warp();
    
    float magnitude = velocity.GetMagnitude();
    if (magnitude > speedCap)
    {
        velocity = velocity.Normalize();
        velocity = velocity.Scale(speedCap);
    }
    
    velocity.x -= velocity.x * friction * GetFrameTime();
    velocity.y -= velocity.y * friction * GetFrameTime();
    
    position = position.Add(velocity.Scale(GetFrameTime()));
}

Vector2d Object::Bounce(Object otherObject)
{
    Vector2d thisOffset;
    Vector2d otherOffset;

    float force = otherObject.velocity.Subtract(velocity).GetMagnitude();

    thisOffset = position.Subtract(otherObject.position).Normalize().Scale(force);
    otherOffset = otherObject.position.Subtract(position).Normalize().Scale(force);
    
    velocity = velocity.Add(thisOffset);

    return otherOffset;
}




bool Object::CircleCollision(Object targetObject)
{
    if (position.DistanceToTarget(targetObject.position) < (size + targetObject.size) * (3.f/4.f)) // Are the objects clipping?
    {
        Vector2d awayVector = position.Subtract(targetObject.position);
        awayVector = awayVector.Scale(0.5f);
        position = position.Add(awayVector);
        return false;
    }
    
    if (position.DistanceToTarget(targetObject.position) < size + targetObject.size)
    {
        return true;
    }
    return false;
}
