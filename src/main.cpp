#include <iostream>
#include <raylib.h>

#include <headers/Vector2d.h>
#include <headers/Player.h>
#include <headers/Object.h>
#include <headers/Functions.h>

#include <vector>

using namespace std;

int main()
{
	srand(time(0));
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Vector2d screenCenter = {screenWidth/2, screenHeight/2};

	Color backgroundColor = { 0, 110, 200, 255 }; //Blue, but like nicer

	//Variable Declarations
	
	float currentWindStrength = 0.f;
	float targetWindStrength = 0.f;
	float windTime = 10.f;

	
	Vector2d windDirection = { 0, 0 };

	float spawnTime = 0.f;
	

	float score = 0.f;
	int scoreWhole = 0;

	const char* titleText = "";

	Player player;
	player = SpawnPlayer(screenCenter);
	

	vector <Object> objects; // vector container not Vector2d

	// Game loop starts
	
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
			targetWindStrength = (1000.f + sqrtf(score) * 60);
			windDirection = RandomDirection();
		}
		
		if (windDirection.GetMagnitude() > 0 && currentWindStrength >= 400.f && objects.size() < score/50 + 8 && spawnTime > 3)
		{
			Object spawnedObject = (SpawnObject(RandomizeSpawnPoint(windDirection, 90.f), rand() % 3));
			objects.push_back(spawnedObject);
			
			spawnTime = 0;
		}

		
		if (IsKeyDown(KEY_ESCAPE))
		{
			CloseWindow();
		}

		if (player.isAlive == false && IsKeyDown(KEY_SPACE))
		{
			player = SpawnPlayer(screenCenter);
			score = 0;
			objects.clear();
			targetWindStrength = 0;
			currentWindStrength = 0;
			spawnTime = 0;
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
		
		if (player.isAlive == true)
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
						score += 50;
						objects[i] = SpawnObject(RandomizeSpawnPoint(windDirection, 90.f), 0);
					}

					else if (objects[i].objectType == 2) // Extra Life
					{
						player.lives += 1;
						objects[i] = SpawnObject(RandomizeSpawnPoint(windDirection, 90.f), 0);
					}
				}
			}
		}

		spawnTime += GetFrameTime();

		
		//HUD Elements
		
		if (player.isAlive == true)
		{
			scoreWhole = round(score);
			
			const char* scoreText = TextFormat("Score: %i ", scoreWhole);
			const char* livesText = TextFormat("Lives: %i", player.lives);
			DrawText(scoreText, 10, 10, 50, YELLOW);

			if (player.invincibilityTime < 0)
			{
				DrawText(livesText, 300, 10, 50, GREEN);
			}
			else
			{
				DrawText(livesText, 295, 5, 60, PINK);
			}
		}
		else
		{
			const char* finalScoreText = TextFormat("Final Score: \n      %i", scoreWhole);
			const char* youLoseText = TextFormat("You Crashed");
			DrawText("You Crashed", screenWidth/5, (screenHeight/8)*1, 150, BLACK);
			DrawText(GetLossTitle(score), screenWidth/6, (screenHeight/8)*2, 150, MAROON);
			DrawText(finalScoreText, screenWidth/7, (screenHeight/8)*3, 200, YELLOW);
			DrawText("Press Space to Restart", screenWidth/6, (screenHeight/8)*6, 100, WHITE);
		}
		
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}