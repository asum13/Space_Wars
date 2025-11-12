#include <iostream>
#include <raylib.h>

#include <headers/Vector2d.h>
#include <headers/Player.h>
#include <headers/Object.h>

#include <vector>

using namespace std;

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

Object SpawnObject(Vector2d spawnPoint, int objectType) // Should be put into a functions file
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
	spawnedObject.friction *= spawnedObject.friction / 3 + float(randomNum)/200.0f;
	spawnedObject.size *= 1.5;
	return spawnedObject;
}



int main()
{
	srand(time(0));
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Vector2d screenCenter = {screenWidth/2, screenHeight/2};

	Color backgroundColor = { 0, 110, 200, 255 }; //Blue, but like nicer

	float currentWindStrength = 0.f;
	float targetWindStrength = 0.f;
	float windTime = 10.f;

	
	Vector2d windDirection = { 0, 0 };

	float spawnTime = 0.f;
	

	float score = 0.f;
	int scoreWhole = 0;

	const char* titleText = "";

	

	Player player;
	player.position = screenCenter;
	player.acceleration = 20.f;
	player.friction = 1.7f;
	player.turnSpeed = 3.f;
	player.speedCap = 3000.f;
	player.mainColor = ORANGE;
	

	vector <Object> objects; // vector container not Vector2d
	
	
	InitWindow(screenWidth, screenHeight, "ScallyWars");

	SetTargetFPS(60);
	
	while (!WindowShouldClose()) 
	{

		if (currentWindStrength < targetWindStrength)
		{
			currentWindStrength += ((targetWindStrength / windTime) * GetFrameTime());
		}
		else
		{
			currentWindStrength = 0;
			targetWindStrength = (1000.f + score * 4);
			windDirection = RandomDirection();
		}
		
		if (windDirection.GetMagnitude() > 0 && currentWindStrength >= 400.f && objects.size() < 10 && spawnTime > 1)
		{
			Object spawnedIceberg = (SpawnObject(RandomizeSpawnPoint(windDirection, 90.f), 0));
			objects.push_back(spawnedIceberg);
			
			spawnTime = 0;
		}

		
		if (IsKeyDown(KEY_ESCAPE))
		{
			CloseWindow();
		}

		// Remove before game release


		if (IsKeyPressed(KEY_B))
		{
			windDirection = RandomDirection();
		}
		
		if (IsKeyDown(KEY_SPACE))
		{
			windDirection = {0,0};
		}
		if (IsKeyDown(KEY_J))
		{
			windDirection = {-1,0};
		}
		if (IsKeyDown(KEY_L))
		{
			windDirection = {1,0};
		}
		if (IsKeyDown(KEY_K))
		{
			windDirection = {0,1};
		}
		if (IsKeyDown(KEY_I))
		{
			windDirection = {0,-1};
		}

		
		
		

		//Begin Drawing
		
		BeginDrawing();

		ClearBackground(backgroundColor);

		//Player update
		
		if (player.lives > 0)
		{
			player.UpdatePlayer();
			player.ApplyWind(windDirection, currentWindStrength);
			
			score += 3 * GetFrameTime();
		}


		//Objects update
		
		if (objects.size() > 0)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				objects[i].UpdatePhysics();
				objects[i].ApplyWind(windDirection, currentWindStrength);
				objects[i].DrawAsCircle();

				//Collision
				for (int j = i + 1; j < objects.size(); j++)
				{
					if (objects[i].CircleCollision(objects[j]))
					{
						objects[j].velocity = objects[i].Bounce(objects[j]);
					}
				}
				
				if (objects[i].CircleCollision(player))
				{
					player.velocity = objects[i].Bounce(player);
					
					if (objects[i].objectType == 0) // Icebergs
					{
						player.TakeDamage();
					}
					
					else if (objects[i].objectType == 1) // Treasure
					{
						score += 100;
						objects[i].objectType = 0;
						objects[i].mainColor = PINK;
						objects[i].position = RandomizeSpawnPoint(windDirection, 90.f);
						objects[i].velocity = {0,0};
					}

					else if (objects[i].objectType == 2) // Extra Life
					{
						player.lives += 1;
						objects[i].objectType = 0;
						objects[i].mainColor = PINK;
						objects[i].position = RandomizeSpawnPoint(windDirection, 90.f);
						objects[i].velocity = {0,0};
					}
				}
			}
		}

		spawnTime += GetFrameTime();
		
		//HUD Elements

		scoreWhole = round(score);
		
		const char* scoreText = TextFormat("Score: %i ", scoreWhole);
		const char* livesText = TextFormat("Lives: %i", player.lives);

		if (player.lives <= 0)
		{
			const char* titleText = TextFormat("  You Crashed \n ScallyWag \nTotal Score: \n      %i", scoreWhole);
			DrawText(titleText, screenWidth/8, screenHeight/4, 200, WHITE);
		}

		
		DrawText(scoreText, 10, 10, 50, YELLOW);

		if (player.invincibilityTime < 0)
		{
			DrawText(livesText, 300, 10, 50, GREEN);
		}
		else
		{
			DrawText(livesText, 295, 5, 60, PINK);
		}
		
		
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}