#pragma once

class Vector2d
{
public:
    
    float x, y;

    Vector2d Add(Vector2d addedVector) // (x1,y1) + (x2, y2)
    ;

    Vector2d Subtract(Vector2d subtractingVector) // (x1,y1) - (x2, y2)
    ;

    Vector2d Scale(float scale) // (x,y) * S
    ;

    float GetMagnitude() //Pythagorean theorem
    ;

    float DistanceToTarget(Vector2d target) // Subtract then GetMagnitude
    ;

    Vector2d Normalize() //Set magnitude to 1
    ;
};