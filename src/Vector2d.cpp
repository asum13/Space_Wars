#include "Headers/Vector2d.h"
#include <vector>

Vector2d Vector2d::Add(Vector2d addedVector)
{
    float outVectorX = x + addedVector.x;
    float outVectorY = y + addedVector.y;
    return Vector2d { outVectorX, outVectorY };
}

Vector2d Vector2d::Subtract(Vector2d subtractingVector)
{
    float outVectorX = x - subtractingVector.x;
    float outVectorY = y - subtractingVector.y;
    return Vector2d { outVectorX, outVectorY };
}

Vector2d Vector2d::Scale(float scale)
{
    float outVectorX = x * scale;
    float outVectorY = y * scale;
    return Vector2d { outVectorX, outVectorY };
}

float Vector2d::GetMagnitude()
{
    float magnitudeSquared = x * x + y * y;
    float magnitude = sqrtf(magnitudeSquared);
    return magnitude;
}

float Vector2d::DistanceToTarget(Vector2d target)
{
    Vector2d vectorToTarget = Subtract(target);
    float distance = vectorToTarget.GetMagnitude();
    return distance;
}

Vector2d Vector2d::Normalize()
{
    float magnitude = GetMagnitude();
			
    if (magnitude == 0) // Don't divide by 0
    {
        return Vector2d { 0, 0 };
    }

    float normalizedVectorX = x / magnitude;
    float normalizedVectorY = y / magnitude;
    Vector2d normalizedVector{normalizedVectorX, normalizedVectorY};

    return normalizedVector;
}
