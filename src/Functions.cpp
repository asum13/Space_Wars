#include "headers/Functions.h"
#include "headers/Vector2d.h"
#include "headers/Object.h"
#include "headers/Player.h"
#include "raylib.h"
#include "iostream"

Vector2d RandomizeSpawnPoint(Vector2d windDirection, float borderOffset)
{
    Vector2d spawnPoint;
	
    if (windDirection.x == 1)
    {
        spawnPoint.x = -borderOffset;
        spawnPoint.y = rand() % GetScreenHeight();
    }
    else if (windDirection.x == -1)
    {
        spawnPoint.x = GetScreenWidth() + borderOffset;
        spawnPoint.y = rand() % GetScreenHeight();
    }
    else if (windDirection.y == 1)
    {
        spawnPoint.x = rand() % GetScreenWidth();
        spawnPoint.y = -borderOffset;
    }
    else
    {
        spawnPoint.x = rand() % GetScreenWidth();
        spawnPoint.y = GetScreenHeight() + borderOffset;
    }
	
    return spawnPoint;
}

Vector2d RandomDirection()
{
    int randomNum = rand() % 4;
    if (randomNum == 0)
    {
        return {1,0};
    }
    if (randomNum == 1)
    {
        return {-1,0};
    }
    if (randomNum == 2)
    {
        return {0,1};
    }
    if (randomNum == 3)
    {
        return {0,-1};
    }
}

Object SpawnObject(Vector2d spawnPoint, int objectType)
{
	
    Object spawnedObject;
    spawnedObject.objectType = objectType;

    if (objectType == 0)
    {
        spawnedObject.mainColor = PINK;
        spawnedObject.size = 60.f;
        
    }
    if (objectType == 1)
    {
        spawnedObject.mainColor = YELLOW;
        spawnedObject.size = 45.f;
    }
    else if (objectType == 2)
    {
        spawnedObject.mainColor = GREEN;
        spawnedObject.size = 45.f;
    }

    spawnedObject.position = spawnPoint;
	
    int randomNum = rand() % 101;
    spawnedObject.friction *= (spawnedObject.friction / 3 + float(randomNum)/200.0f); // Objects randomly get higher and smaller friction making them move at differents speeds.
    return spawnedObject;
}

Player SpawnPlayer(Vector2d spawnPoint)
{
    Player spawnedPlayer;
    spawnedPlayer.position = spawnPoint;
    spawnedPlayer.acceleration = 25.f;
    spawnedPlayer.size = 40.f;
    spawnedPlayer.lives = 3;
    spawnedPlayer.friction = 3.f;
    spawnedPlayer.turnSpeed = 2.f;
    spawnedPlayer.speedCap = 3000.f;
    spawnedPlayer.mainColor = ORANGE;
    return spawnedPlayer;
}

const char* GetLossTitle(float score)
{
    if (score < 100.f)
    {
        return "Powder Monkey";
    }
    else if (score < 250.f)
    {
        return "  Scoundrel";
    }
    else if (score < 500.f)
    {
        return "  Scallywag";
    }
    else if (score < 1000.f)
    {
        return "    Captain";
    }
    else
    {
        return "    Legend";
    }
}