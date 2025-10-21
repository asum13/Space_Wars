#include <iostream>
#include <raylib.h>
#include <src/Vector2d.h>
#include <src/Player.h>

using namespace std;


int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Vector2d screenCenter = {screenWidth/2, screenHeight/2};

	Player player;
	player.position = screenCenter;

	Player iceberg;
	iceberg.position = { screenWidth / 2 + 500, screenHeight / 2 };
	iceberg.shipColor = PINK;
	
	
	
	InitWindow(screenWidth, screenHeight, "ScallyWars");

	SetTargetFPS(60);
	
	while (!WindowShouldClose()) 
	{
		BeginDrawing();

		ClearBackground(BLUE);

		player.Update();
		player.Draw();
		player.CheckInput();

		iceberg.Update();
		iceberg.Draw();

		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}