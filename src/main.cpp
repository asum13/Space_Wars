#include <iostream>
#include <raylib.h>

#include <headers/Vector2d.h>
#include <headers/Player.h>
#include <headers/Object.h>

#include <vector>

using namespace std;

Object SpawnIceberg(Vector2d windDirection)
{
	
	Object iceberg;
	if (windDirection.x == 1 && windDirection.y == 0)
	{
        iceberg.position.x = -60;
		iceberg.position.y = rand() % GetScreenHeight();
	}
	else if (windDirection.x == -1 && windDirection.y == 0)
	{
		iceberg.position.x = -GetScreenWidth() + 20;
		iceberg.position.y = GetScreenHeight() / 2;
	}
	else if (windDirection.x == 0 && windDirection.y == 1)
	{
		iceberg.position.x = GetScreenWidth() / 2;
		iceberg.position.y = -20;
	}
	else
	{
		iceberg.position.x = GetScreenWidth() / 2;
		iceberg.position.y = GetScreenHeight() + 20;
	}
	int randomNum = rand() % 101;
	iceberg.friction *= float(randomNum)/100.0f;
	cout << iceberg.friction << endl;
	return iceberg;
}

int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Vector2d screenCenter = {screenWidth/2, screenHeight/2};

	Color backgroundColor = { 0, 110, 200, 255 }; //Blue

	Player player;
	player.position = screenCenter;
	player.mainColor = ORANGE;


	vector <Object> objects; // vector container not Vector2d

	float windStrength = 1000.f;
	Vector2d windDirection = { 1, 0 };

	float score = 0;
	int scoreWhole = 0;
	const char* scoreText;
	
	InitWindow(screenWidth, screenHeight, "ScallyWars");

	SetTargetFPS(60);
	
	while (!WindowShouldClose()) 
	{
		
		
		player.invincibilityTime -= GetFrameTime();
		if (player.invincibilityTime > 0)
		{
			player.mainColor = LIGHTGRAY;
		}
		else
		{
			player.mainColor = ORANGE;
		}

		if (windDirection.GetMagnitude() == 1 && objects.size() < 6)
		{
			objects.push_back(SpawnIceberg(windDirection));
		}

		
		scoreWhole = round(score);
		scoreText = TextFormat("Score: %i ", scoreWhole);

		const char* livesText = TextFormat("Lives: %i", player.lives);


		
		BeginDrawing();

		ClearBackground(backgroundColor);

		if (player.isAlive)
		{
			player.Update();
			player.CheckInput();
			player.ApplyWind(windDirection, windStrength);
			player.DrawPlayer();
			
			score += 3 * GetFrameTime();
		}
		
		if (objects.size() > 0)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				objects[i].Update();
				objects[i].ApplyWind(windDirection, windStrength);
				objects[i].DrawAsCircle();
				if (objects[i].CircleCollision(player))
				{
					if (player.invincibilityTime < 0)
					{
						player.lives--;
						if (player.lives > 0)
						{
							player.invincibilityTime = 2.f;
							objects.erase(objects.begin() + i);
						}
						else
						{
							player.isAlive = false;
							player.position = {100000, 100000}; // Player *Disappears*
						}
					}
				}
			}
		}

		
		
		//HUD Elements
		DrawText(scoreText, 10, 10, 50, WHITE);
		DrawText(livesText, 300, 10, 50, WHITE);
		
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}