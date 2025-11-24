#pragma once
#include "headers/Vector2d.h"
#include "headers/Object.h"
#include "headers/Player.h"

Vector2d RandomizeSpawnPoint(Vector2d windDirection, float borderOffset);

Vector2d RandomDirection();

Object SpawnObject(Vector2d spawnPoint, int objectType);

Player SpawnPlayer(Vector2d spawnPoint);

const char* GetLossTitle(float score);