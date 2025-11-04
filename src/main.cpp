#include <iostream>
#include <raylib.h>

#include <headers/Vector2d.h>
#include <headers/Player.h>
#include <headers/Object.h>

#include <vector>

using namespace std;

Object SpawnIceberg(Vector2d windDirection) // Should put into a functions file
{
	
	Object iceberg;
	float borderOffset = iceberg.borderOffset;
	if (windDirection.x == 1)
	{
        iceberg.position.x = -borderOffset;
		iceberg.position.y = rand() % GetScreenHeight();
	}
	else if (windDirection.x == -1)
	{
		iceberg.position.x = GetScreenWidth() + borderOffset;
		iceberg.position.y = rand() % GetScreenHeight();
	}
	else if (windDirection.y == 1)
	{
		iceberg.position.x = rand() % GetScreenWidth();
		iceberg.position.y = -borderOffset;
	}
	else
	{
		iceberg.position.x = rand() % GetScreenWidth();
		iceberg.position.y = GetScreenHeight() + borderOffset;
	}
	int randomNum = rand() % 101;
	iceberg.friction *= iceberg.friction / 3 + float(randomNum)/200.0f;
	iceberg.size *= 1.5;
	return iceberg;
}

int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Vector2d screenCenter = {screenWidth/2, screenHeight/2};

	Color backgroundColor = { 0, 110, 200, 255 }; //Blue

	srand(time(0));

	Player player;
	player.position = screenCenter;
	player.acceleration = 20.f;
	player.friction = 1.7f;
	player.turnSpeed = 3.f;
	player.speedCap = 3000.f;
	player.mainColor = ORANGE;



	vector <Object> objects; // vector container not Vector2d

	float windStrength = 1500.f;
	Vector2d windDirection = { 0, 0 };

	float score = 0;
	int scoreWhole = 0;
	const char* scoreText;

	float spawnTime = 0.f;
	
	InitWindow(screenWidth, screenHeight, "ScallyWars");

	SetTargetFPS(60);
	
	while (!WindowShouldClose()) 
	{

		
		if (windDirection.GetMagnitude() > 0 && objects.size() < 10 && spawnTime > 1)
		{
			objects.push_back(SpawnIceberg(windDirection));
			spawnTime = 0;
		}

		
		if (IsKeyDown(KEY_ESCAPE))
		{
			CloseWindow();
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

		
		scoreWhole = round(score);
		scoreText = TextFormat("Score: %i ", scoreWhole);

		const char* livesText = TextFormat("Lives: %i", player.lives);


		
		BeginDrawing();

		ClearBackground(backgroundColor);

		if (player.isAlive)
		{
			player.UpdatePlayer();
			player.ApplyWind(windDirection, windStrength);
			
			score += 3 * GetFrameTime();
		}
		
		if (objects.size() > 0)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				objects[i].UpdatePhysics();
				objects[i].ApplyWind(windDirection, windStrength);
				objects[i].DrawAsCircle();
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
					player.TakeDamage();
				}
			}
		}

		spawnTime += GetFrameTime();
		
		//HUD Elements
		DrawText(scoreText, 10, 10, 50, YELLOW);
		DrawText(livesText, 300, 10, 50, GREEN);
		
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}