#include <iostream>
#include <raylib.h>
#include <src/Vector2d.h>
#include <src/Player.h>

using namespace std;



int main()
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

	Player player;
	player.position = { screenWidth / 2, screenHeight / 2 };
	
	Vector2d screenCenter = {screenWidth/2, screenHeight/2};
	
	InitWindow(screenWidth, screenHeight, "Space Wars");

	SetTargetFPS(60);
	
	while (!WindowShouldClose()) 
	{
		BeginDrawing();

		ClearBackground(BLACK);
		
		player.Draw();
		player.Update();
		player.CheckInput();
		cout << player.position.x << endl;

		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}